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
struct ef4_link_state {int up; } ;
struct ef4_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* type; struct ef4_link_state link_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* check_mac_fault ) (struct ef4_nic*) ;int /*<<< orphan*/  (* monitor ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub2 (struct ef4_nic*) ; 

__attribute__((used)) static int ef4_wait_for_link(struct ef4_nic *efx)
{
	struct ef4_link_state *link_state = &efx->link_state;
	int count, link_up_count = 0;
	bool link_up;

	for (count = 0; count < 40; count++) {
		schedule_timeout_uninterruptible(HZ / 10);

		if (efx->type->monitor != NULL) {
			mutex_lock(&efx->mac_lock);
			efx->type->monitor(efx);
			mutex_unlock(&efx->mac_lock);
		}

		mutex_lock(&efx->mac_lock);
		link_up = link_state->up;
		if (link_up)
			link_up = !efx->type->check_mac_fault(efx);
		mutex_unlock(&efx->mac_lock);

		if (link_up) {
			if (++link_up_count == 2)
				return 0;
		} else {
			link_up_count = 0;
		}
	}

	return -ETIMEDOUT;
}