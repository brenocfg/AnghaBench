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
typedef  scalar_t__ u32 ;
struct rmid_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  busy; int /*<<< orphan*/  rmid; } ;
struct rdt_resource {scalar_t__ num_rmid; } ;
struct rdt_domain {int /*<<< orphan*/  rmid_busy_llc; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_L3 ; 
 struct rmid_entry* __rmid_entry (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ find_next_bit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rdt_resource* rdt_resources_all ; 
 int /*<<< orphan*/  rmid_dirty (struct rmid_entry*) ; 
 int /*<<< orphan*/  rmid_free_lru ; 
 int /*<<< orphan*/  rmid_limbo_count ; 

void __check_limbo(struct rdt_domain *d, bool force_free)
{
	struct rmid_entry *entry;
	struct rdt_resource *r;
	u32 crmid = 1, nrmid;

	r = &rdt_resources_all[RDT_RESOURCE_L3];

	/*
	 * Skip RMID 0 and start from RMID 1 and check all the RMIDs that
	 * are marked as busy for occupancy < threshold. If the occupancy
	 * is less than the threshold decrement the busy counter of the
	 * RMID and move it to the free list when the counter reaches 0.
	 */
	for (;;) {
		nrmid = find_next_bit(d->rmid_busy_llc, r->num_rmid, crmid);
		if (nrmid >= r->num_rmid)
			break;

		entry = __rmid_entry(nrmid);
		if (force_free || !rmid_dirty(entry)) {
			clear_bit(entry->rmid, d->rmid_busy_llc);
			if (!--entry->busy) {
				rmid_limbo_count--;
				list_add_tail(&entry->list, &rmid_free_lru);
			}
		}
		crmid = nrmid + 1;
	}
}