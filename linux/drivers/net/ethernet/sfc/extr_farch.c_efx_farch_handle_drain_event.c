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
struct efx_nic {int /*<<< orphan*/  flush_wq; int /*<<< orphan*/  active_queues; } ;
struct efx_channel {struct efx_nic* efx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ efx_farch_flush_wake (struct efx_nic*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efx_farch_handle_drain_event(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;

	WARN_ON(atomic_read(&efx->active_queues) == 0);
	atomic_dec(&efx->active_queues);
	if (efx_farch_flush_wake(efx))
		wake_up(&efx->flush_wq);
}