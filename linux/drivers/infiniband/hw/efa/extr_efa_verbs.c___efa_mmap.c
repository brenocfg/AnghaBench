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
typedef  int u64 ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int /*<<< orphan*/  vm_page_prot; } ;
struct efa_ucontext {int /*<<< orphan*/  ibucontext; } ;
struct efa_mmap_entry {int address; int mmap_flag; } ;
struct efa_dev {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
#define  EFA_MMAP_DMA_PAGE 130 
#define  EFA_MMAP_IO_NC 129 
#define  EFA_MMAP_IO_WC 128 
 int EINVAL ; 
 int PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  ibdev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct efa_mmap_entry* mmap_entry_get (struct efa_dev*,struct efa_ucontext*,int,int) ; 
 int /*<<< orphan*/  pfn_to_page (int) ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprot_writecombine (int /*<<< orphan*/ ) ; 
 int rdma_user_mmap_io (int /*<<< orphan*/ *,struct vm_area_struct*,int,int,int /*<<< orphan*/ ) ; 
 int vm_insert_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __efa_mmap(struct efa_dev *dev, struct efa_ucontext *ucontext,
		      struct vm_area_struct *vma, u64 key, u64 length)
{
	struct efa_mmap_entry *entry;
	unsigned long va;
	u64 pfn;
	int err;

	entry = mmap_entry_get(dev, ucontext, key, length);
	if (!entry) {
		ibdev_dbg(&dev->ibdev, "key[%#llx] does not have valid entry\n",
			  key);
		return -EINVAL;
	}

	ibdev_dbg(&dev->ibdev,
		  "Mapping address[%#llx], length[%#llx], mmap_flag[%d]\n",
		  entry->address, length, entry->mmap_flag);

	pfn = entry->address >> PAGE_SHIFT;
	switch (entry->mmap_flag) {
	case EFA_MMAP_IO_NC:
		err = rdma_user_mmap_io(&ucontext->ibucontext, vma, pfn, length,
					pgprot_noncached(vma->vm_page_prot));
		break;
	case EFA_MMAP_IO_WC:
		err = rdma_user_mmap_io(&ucontext->ibucontext, vma, pfn, length,
					pgprot_writecombine(vma->vm_page_prot));
		break;
	case EFA_MMAP_DMA_PAGE:
		for (va = vma->vm_start; va < vma->vm_end;
		     va += PAGE_SIZE, pfn++) {
			err = vm_insert_page(vma, va, pfn_to_page(pfn));
			if (err)
				break;
		}
		break;
	default:
		err = -EINVAL;
	}

	if (err) {
		ibdev_dbg(
			&dev->ibdev,
			"Couldn't mmap address[%#llx] length[%#llx] mmap_flag[%d] err[%d]\n",
			entry->address, length, entry->mmap_flag, err);
		return err;
	}

	return 0;
}