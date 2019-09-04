#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibmvmc_hmc {scalar_t__ state; unsigned long index; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {unsigned long max_hmc_index; } ;

/* Variables and functions */
 struct ibmvmc_hmc* hmcs ; 
 scalar_t__ ibmhmc_state_free ; 
 scalar_t__ ibmhmc_state_initial ; 
 TYPE_1__ ibmvmc ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct ibmvmc_hmc *ibmvmc_get_free_hmc(void)
{
	unsigned long i;
	unsigned long flags;

	/*
	 * Find an available HMC connection.
	 */
	for (i = 0; i <= ibmvmc.max_hmc_index; i++) {
		spin_lock_irqsave(&hmcs[i].lock, flags);
		if (hmcs[i].state == ibmhmc_state_free) {
			hmcs[i].index = i;
			hmcs[i].state = ibmhmc_state_initial;
			spin_unlock_irqrestore(&hmcs[i].lock, flags);
			return &hmcs[i];
		}
		spin_unlock_irqrestore(&hmcs[i].lock, flags);
	}

	return NULL;
}