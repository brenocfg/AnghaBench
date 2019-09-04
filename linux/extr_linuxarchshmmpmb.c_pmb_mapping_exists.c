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
struct pmb_entry {unsigned long vpn; unsigned long size; scalar_t__ ppn; struct pmb_entry* link; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct pmb_entry*) ; 
 struct pmb_entry* pmb_entry_list ; 
 int /*<<< orphan*/  pmb_map ; 
 int /*<<< orphan*/  pmb_rwlock ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pmb_mapping_exists(unsigned long vaddr, phys_addr_t phys,
			       unsigned long size)
{
	int i;

	read_lock(&pmb_rwlock);

	for (i = 0; i < ARRAY_SIZE(pmb_entry_list); i++) {
		struct pmb_entry *pmbe, *iter;
		unsigned long span;

		if (!test_bit(i, pmb_map))
			continue;

		pmbe = &pmb_entry_list[i];

		/*
		 * See if VPN and PPN are bounded by an existing mapping.
		 */
		if ((vaddr < pmbe->vpn) || (vaddr >= (pmbe->vpn + pmbe->size)))
			continue;
		if ((phys < pmbe->ppn) || (phys >= (pmbe->ppn + pmbe->size)))
			continue;

		/*
		 * Now see if we're in range of a simple mapping.
		 */
		if (size <= pmbe->size) {
			read_unlock(&pmb_rwlock);
			return true;
		}

		span = pmbe->size;

		/*
		 * Finally for sizes that involve compound mappings, walk
		 * the chain.
		 */
		for (iter = pmbe->link; iter; iter = iter->link)
			span += iter->size;

		/*
		 * Nothing else to do if the range requirements are met.
		 */
		if (size <= span) {
			read_unlock(&pmb_rwlock);
			return true;
		}
	}

	read_unlock(&pmb_rwlock);
	return false;
}