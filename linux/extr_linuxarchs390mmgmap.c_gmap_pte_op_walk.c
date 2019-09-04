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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned long _SEGMENT_ENTRY_INVALID ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 unsigned long* gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/ * pte_alloc_map_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 

__attribute__((used)) static pte_t *gmap_pte_op_walk(struct gmap *gmap, unsigned long gaddr,
			       spinlock_t **ptl)
{
	unsigned long *table;

	BUG_ON(gmap_is_shadow(gmap));
	/* Walk the gmap page table, lock and get pte pointer */
	table = gmap_table_walk(gmap, gaddr, 1); /* get segment pointer */
	if (!table || *table & _SEGMENT_ENTRY_INVALID)
		return NULL;
	return pte_alloc_map_lock(gmap->mm, (pmd_t *) table, gaddr, ptl);
}