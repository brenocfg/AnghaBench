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
struct pasid_state {int /*<<< orphan*/  mm; int /*<<< orphan*/  mn; } ;
struct device_state {int max_pasids; int pasid_levels; scalar_t__ states; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pasid_states_level1 (scalar_t__) ; 
 int /*<<< orphan*/  free_pasid_states_level2 (scalar_t__) ; 
 struct pasid_state* get_pasid_state (struct device_state*,int) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device_state (struct device_state*) ; 
 int /*<<< orphan*/  put_pasid_state (struct pasid_state*) ; 
 int /*<<< orphan*/  put_pasid_state_wait (struct pasid_state*) ; 

__attribute__((used)) static void free_pasid_states(struct device_state *dev_state)
{
	struct pasid_state *pasid_state;
	int i;

	for (i = 0; i < dev_state->max_pasids; ++i) {
		pasid_state = get_pasid_state(dev_state, i);
		if (pasid_state == NULL)
			continue;

		put_pasid_state(pasid_state);

		/*
		 * This will call the mn_release function and
		 * unbind the PASID
		 */
		mmu_notifier_unregister(&pasid_state->mn, pasid_state->mm);

		put_pasid_state_wait(pasid_state); /* Reference taken in
						      amd_iommu_bind_pasid */

		/* Drop reference taken in amd_iommu_bind_pasid */
		put_device_state(dev_state);
	}

	if (dev_state->pasid_levels == 2)
		free_pasid_states_level2(dev_state->states);
	else if (dev_state->pasid_levels == 1)
		free_pasid_states_level1(dev_state->states);
	else
		BUG_ON(dev_state->pasid_levels != 0);

	free_page((unsigned long)dev_state->states);
}