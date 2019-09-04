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
struct vl_arb_cache {int /*<<< orphan*/  lock; } ;
struct hfi1_pportdata {struct vl_arb_cache* vl_arb_cache; } ;

/* Variables and functions */
 int HI_PRIO_TABLE ; 
 int LO_PRIO_TABLE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct vl_arb_cache *
vl_arb_lock_cache(struct hfi1_pportdata *ppd, int idx)
{
	if (idx != LO_PRIO_TABLE && idx != HI_PRIO_TABLE)
		return NULL;
	spin_lock(&ppd->vl_arb_cache[idx].lock);
	return &ppd->vl_arb_cache[idx];
}