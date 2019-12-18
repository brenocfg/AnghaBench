#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vm_area_struct {unsigned long vm_pgoff; unsigned long vm_end; unsigned long vm_start; int vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct qedr_ucontext {unsigned long dpi; unsigned long dpi_size; } ;
struct qedr_dev {unsigned long db_phys_addr; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,void*,void*,void*,void*,unsigned long) ; 
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,...) ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int VM_READ ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 struct qedr_ucontext* get_qedr_ucontext (struct ib_ucontext*) ; 
 int io_remap_pfn_range (struct vm_area_struct*,int,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_search_mmap (struct qedr_ucontext*,unsigned long,unsigned long) ; 

int qedr_mmap(struct ib_ucontext *context, struct vm_area_struct *vma)
{
	struct qedr_ucontext *ucontext = get_qedr_ucontext(context);
	struct qedr_dev *dev = get_qedr_dev(context->device);
	unsigned long phys_addr = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long len = (vma->vm_end - vma->vm_start);
	unsigned long dpi_start;

	dpi_start = dev->db_phys_addr + (ucontext->dpi * ucontext->dpi_size);

	DP_DEBUG(dev, QEDR_MSG_INIT,
		 "mmap invoked with vm_start=0x%pK, vm_end=0x%pK,vm_pgoff=0x%pK; dpi_start=0x%pK dpi_size=0x%x\n",
		 (void *)vma->vm_start, (void *)vma->vm_end,
		 (void *)vma->vm_pgoff, (void *)dpi_start, ucontext->dpi_size);

	if ((vma->vm_start & (PAGE_SIZE - 1)) || (len & (PAGE_SIZE - 1))) {
		DP_ERR(dev,
		       "failed mmap, addresses must be page aligned: start=0x%pK, end=0x%pK\n",
		       (void *)vma->vm_start, (void *)vma->vm_end);
		return -EINVAL;
	}

	if (!qedr_search_mmap(ucontext, phys_addr, len)) {
		DP_ERR(dev, "failed mmap, vm_pgoff=0x%lx is not authorized\n",
		       vma->vm_pgoff);
		return -EINVAL;
	}

	if (phys_addr < dpi_start ||
	    ((phys_addr + len) > (dpi_start + ucontext->dpi_size))) {
		DP_ERR(dev,
		       "failed mmap, pages are outside of dpi; page address=0x%pK, dpi_start=0x%pK, dpi_size=0x%x\n",
		       (void *)phys_addr, (void *)dpi_start,
		       ucontext->dpi_size);
		return -EINVAL;
	}

	if (vma->vm_flags & VM_READ) {
		DP_ERR(dev, "failed mmap, cannot map doorbell bar for read\n");
		return -EINVAL;
	}

	vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	return io_remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff, len,
				  vma->vm_page_prot);
}