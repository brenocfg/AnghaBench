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
struct gmap {int /*<<< orphan*/  mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int _PAGE_ENTRIES ; 
 int /*<<< orphan*/  bitmap_fill (unsigned long*,int) ; 
 int /*<<< orphan*/  gmap_pmd_op_end (struct gmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gmap_pmd_op_walk (struct gmap*,unsigned long) ; 
 scalar_t__ gmap_test_and_clear_dirty_pmd (struct gmap*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_alloc_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 scalar_t__ ptep_test_and_clear_uc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gmap_sync_dirty_log_pmd(struct gmap *gmap, unsigned long bitmap[4],
			     unsigned long gaddr, unsigned long vmaddr)
{
	int i;
	pmd_t *pmdp;
	pte_t *ptep;
	spinlock_t *ptl;

	pmdp = gmap_pmd_op_walk(gmap, gaddr);
	if (!pmdp)
		return;

	if (pmd_large(*pmdp)) {
		if (gmap_test_and_clear_dirty_pmd(gmap, pmdp, gaddr))
			bitmap_fill(bitmap, _PAGE_ENTRIES);
	} else {
		for (i = 0; i < _PAGE_ENTRIES; i++, vmaddr += PAGE_SIZE) {
			ptep = pte_alloc_map_lock(gmap->mm, pmdp, vmaddr, &ptl);
			if (!ptep)
				continue;
			if (ptep_test_and_clear_uc(gmap->mm, vmaddr, ptep))
				set_bit(i, bitmap);
			spin_unlock(ptl);
		}
	}
	gmap_pmd_op_end(gmap, pmdp);
}