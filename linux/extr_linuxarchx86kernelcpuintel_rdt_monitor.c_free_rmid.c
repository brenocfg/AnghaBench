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
typedef  int /*<<< orphan*/  u32 ;
struct rmid_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct rmid_entry* __rmid_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_rmid_to_limbo (struct rmid_entry*) ; 
 scalar_t__ is_llc_occupancy_enabled () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int /*<<< orphan*/  rmid_free_lru ; 

void free_rmid(u32 rmid)
{
	struct rmid_entry *entry;

	if (!rmid)
		return;

	lockdep_assert_held(&rdtgroup_mutex);

	entry = __rmid_entry(rmid);

	if (is_llc_occupancy_enabled())
		add_rmid_to_limbo(entry);
	else
		list_add_tail(&entry->list, &rmid_free_lru);
}