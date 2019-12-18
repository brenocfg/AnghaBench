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
typedef  unsigned int u64 ;
struct vm_area_struct {int vm_flags; unsigned int vm_pgoff; scalar_t__ vm_start; scalar_t__ vm_end; int /*<<< orphan*/ * vm_private_data; } ;
struct qib_devdata {unsigned int uregbase; int ureg_align; unsigned int palign; unsigned int pioavailregs_phys; int /*<<< orphan*/  pcidev; scalar_t__ pioavailregs_dma; } ;
struct qib_ctxtdata {int ctxt; unsigned int subctxt_cnt; unsigned int piocnt; unsigned int piobufs; unsigned int rcvegr_phys; void* rcvhdrq; void* rcvhdrtail_kvaddr; scalar_t__ rcvhdrqtailaddr_phys; int /*<<< orphan*/  rcvhdrq_size; scalar_t__ rcvhdrq_phys; struct qib_devdata* dd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_SHARED ; 
 struct qib_ctxtdata* ctxt_fp (struct file*) ; 
 int mmap_kvaddr (struct vm_area_struct*,unsigned int,struct qib_ctxtdata*,int) ; 
 int mmap_piobufs (struct vm_area_struct*,struct qib_devdata*,struct qib_ctxtdata*,unsigned int,unsigned int) ; 
 int mmap_rcvegrbufs (struct vm_area_struct*,struct qib_ctxtdata*) ; 
 int mmap_ureg (struct vm_area_struct*,struct qib_devdata*,unsigned int) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int,unsigned long long,scalar_t__) ; 
 int qib_mmap_mem (struct vm_area_struct*,struct qib_ctxtdata*,int /*<<< orphan*/ ,void*,int,char*) ; 
 int subctxt_fp (struct file*) ; 

__attribute__((used)) static int qib_mmapf(struct file *fp, struct vm_area_struct *vma)
{
	struct qib_ctxtdata *rcd;
	struct qib_devdata *dd;
	u64 pgaddr, ureg;
	unsigned piobufs, piocnt;
	int ret, match = 1;

	rcd = ctxt_fp(fp);
	if (!rcd || !(vma->vm_flags & VM_SHARED)) {
		ret = -EINVAL;
		goto bail;
	}
	dd = rcd->dd;

	/*
	 * This is the qib_do_user_init() code, mapping the shared buffers
	 * and per-context user registers into the user process. The address
	 * referred to by vm_pgoff is the file offset passed via mmap().
	 * For shared contexts, this is the kernel vmalloc() address of the
	 * pages to share with the master.
	 * For non-shared or master ctxts, this is a physical address.
	 * We only do one mmap for each space mapped.
	 */
	pgaddr = vma->vm_pgoff << PAGE_SHIFT;

	/*
	 * Check for 0 in case one of the allocations failed, but user
	 * called mmap anyway.
	 */
	if (!pgaddr)  {
		ret = -EINVAL;
		goto bail;
	}

	/*
	 * Physical addresses must fit in 40 bits for our hardware.
	 * Check for kernel virtual addresses first, anything else must
	 * match a HW or memory address.
	 */
	ret = mmap_kvaddr(vma, pgaddr, rcd, subctxt_fp(fp));
	if (ret) {
		if (ret > 0)
			ret = 0;
		goto bail;
	}

	ureg = dd->uregbase + dd->ureg_align * rcd->ctxt;
	if (!rcd->subctxt_cnt) {
		/* ctxt is not shared */
		piocnt = rcd->piocnt;
		piobufs = rcd->piobufs;
	} else if (!subctxt_fp(fp)) {
		/* caller is the master */
		piocnt = (rcd->piocnt / rcd->subctxt_cnt) +
			 (rcd->piocnt % rcd->subctxt_cnt);
		piobufs = rcd->piobufs +
			dd->palign * (rcd->piocnt - piocnt);
	} else {
		unsigned slave = subctxt_fp(fp) - 1;

		/* caller is a slave */
		piocnt = rcd->piocnt / rcd->subctxt_cnt;
		piobufs = rcd->piobufs + dd->palign * piocnt * slave;
	}

	if (pgaddr == ureg)
		ret = mmap_ureg(vma, dd, ureg);
	else if (pgaddr == piobufs)
		ret = mmap_piobufs(vma, dd, rcd, piobufs, piocnt);
	else if (pgaddr == dd->pioavailregs_phys)
		/* in-memory copy of pioavail registers */
		ret = qib_mmap_mem(vma, rcd, PAGE_SIZE,
				   (void *) dd->pioavailregs_dma, 0,
				   "pioavail registers");
	else if (pgaddr == rcd->rcvegr_phys)
		ret = mmap_rcvegrbufs(vma, rcd);
	else if (pgaddr == (u64) rcd->rcvhdrq_phys)
		/*
		 * The rcvhdrq itself; multiple pages, contiguous
		 * from an i/o perspective.  Shared contexts need
		 * to map r/w, so we allow writing.
		 */
		ret = qib_mmap_mem(vma, rcd, rcd->rcvhdrq_size,
				   rcd->rcvhdrq, 1, "rcvhdrq");
	else if (pgaddr == (u64) rcd->rcvhdrqtailaddr_phys)
		/* in-memory copy of rcvhdrq tail register */
		ret = qib_mmap_mem(vma, rcd, PAGE_SIZE,
				   rcd->rcvhdrtail_kvaddr, 0,
				   "rcvhdrq tail");
	else
		match = 0;
	if (!match)
		ret = -EINVAL;

	vma->vm_private_data = NULL;

	if (ret < 0)
		qib_devinfo(dd->pcidev,
			 "mmap Failure %d: off %llx len %lx\n",
			 -ret, (unsigned long long)pgaddr,
			 vma->vm_end - vma->vm_start);
bail:
	return ret;
}