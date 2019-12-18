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
struct usnic_uiom_reg {unsigned long va; int offset; size_t length; int writable; int /*<<< orphan*/  owning_mm; int /*<<< orphan*/  chunk_list; struct usnic_uiom_pd* pd; } ;
struct usnic_uiom_pd {int /*<<< orphan*/  lock; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct usnic_uiom_reg* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMMU_WRITE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  kfree (struct usnic_uiom_reg*) ; 
 struct usnic_uiom_reg* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorted_diff_intervals ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_err (char*,unsigned long,unsigned long,int) ; 
 int usnic_uiom_get_intervals_diff (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int usnic_uiom_get_pages (unsigned long,size_t,int,int,struct usnic_uiom_reg*) ; 
 int usnic_uiom_insert_interval (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int usnic_uiom_map_sorted_intervals (int /*<<< orphan*/ *,struct usnic_uiom_reg*) ; 
 int /*<<< orphan*/  usnic_uiom_put_interval_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usnic_uiom_put_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_uiom_unmap_sorted_intervals (int /*<<< orphan*/ *,struct usnic_uiom_pd*) ; 

struct usnic_uiom_reg *usnic_uiom_reg_get(struct usnic_uiom_pd *pd,
						unsigned long addr, size_t size,
						int writable, int dmasync)
{
	struct usnic_uiom_reg *uiomr;
	unsigned long va_base, vpn_start, vpn_last;
	unsigned long npages;
	int offset, err;
	LIST_HEAD(sorted_diff_intervals);

	/*
	 * Intel IOMMU map throws an error if a translation entry is
	 * changed from read to write.  This module may not unmap
	 * and then remap the entry after fixing the permission
	 * b/c this open up a small windows where hw DMA may page fault
	 * Hence, make all entries to be writable.
	 */
	writable = 1;

	va_base = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	npages = PAGE_ALIGN(size + offset) >> PAGE_SHIFT;
	vpn_start = (addr & PAGE_MASK) >> PAGE_SHIFT;
	vpn_last = vpn_start + npages - 1;

	uiomr = kmalloc(sizeof(*uiomr), GFP_KERNEL);
	if (!uiomr)
		return ERR_PTR(-ENOMEM);

	uiomr->va = va_base;
	uiomr->offset = offset;
	uiomr->length = size;
	uiomr->writable = writable;
	uiomr->pd = pd;

	err = usnic_uiom_get_pages(addr, size, writable, dmasync,
				   uiomr);
	if (err) {
		usnic_err("Failed get_pages vpn [0x%lx,0x%lx] err %d\n",
				vpn_start, vpn_last, err);
		goto out_free_uiomr;
	}

	spin_lock(&pd->lock);
	err = usnic_uiom_get_intervals_diff(vpn_start, vpn_last,
						(writable) ? IOMMU_WRITE : 0,
						IOMMU_WRITE,
						&pd->root,
						&sorted_diff_intervals);
	if (err) {
		usnic_err("Failed disjoint interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_put_pages;
	}

	err = usnic_uiom_map_sorted_intervals(&sorted_diff_intervals, uiomr);
	if (err) {
		usnic_err("Failed map interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_put_intervals;

	}

	err = usnic_uiom_insert_interval(&pd->root, vpn_start, vpn_last,
					(writable) ? IOMMU_WRITE : 0);
	if (err) {
		usnic_err("Failed insert interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		goto out_unmap_intervals;
	}

	usnic_uiom_put_interval_set(&sorted_diff_intervals);
	spin_unlock(&pd->lock);

	return uiomr;

out_unmap_intervals:
	usnic_uiom_unmap_sorted_intervals(&sorted_diff_intervals, pd);
out_put_intervals:
	usnic_uiom_put_interval_set(&sorted_diff_intervals);
out_put_pages:
	usnic_uiom_put_pages(&uiomr->chunk_list, 0);
	spin_unlock(&pd->lock);
	mmdrop(uiomr->owning_mm);
out_free_uiomr:
	kfree(uiomr);
	return ERR_PTR(err);
}