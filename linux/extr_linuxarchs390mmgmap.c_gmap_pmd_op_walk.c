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
struct gmap {int /*<<< orphan*/  guest_table_lock; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 scalar_t__ gmap_table_walk (struct gmap*,unsigned long,int) ; 
 int /*<<< orphan*/  pmd_large (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline pmd_t *gmap_pmd_op_walk(struct gmap *gmap, unsigned long gaddr)
{
	pmd_t *pmdp;

	BUG_ON(gmap_is_shadow(gmap));
	spin_lock(&gmap->guest_table_lock);
	pmdp = (pmd_t *) gmap_table_walk(gmap, gaddr, 1);

	if (!pmdp || pmd_none(*pmdp)) {
		spin_unlock(&gmap->guest_table_lock);
		return NULL;
	}

	/* 4k page table entries are locked via the pte (pte_alloc_map_lock). */
	if (!pmd_large(*pmdp))
		spin_unlock(&gmap->guest_table_lock);
	return pmdp;
}