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
struct efx_nic {int /*<<< orphan*/  mcdi; } ;
struct efx_mcdi_iface {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ MCDI_MODE_FAIL ; 
 scalar_t__ MCDI_MODE_POLL ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_complete_sync (struct efx_mcdi_iface*) ; 

void efx_mcdi_mode_poll(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi;

	if (!efx->mcdi)
		return;

	mcdi = efx_mcdi(efx);
	/* If already in polling mode, nothing to do.
	 * If in fail-fast state, don't switch to polled completion.
	 * FLR recovery will do that later.
	 */
	if (mcdi->mode == MCDI_MODE_POLL || mcdi->mode == MCDI_MODE_FAIL)
		return;

	/* We can switch from event completion to polled completion, because
	 * mcdi requests are always completed in shared memory. We do this by
	 * switching the mode to POLL'd then completing the request.
	 * efx_mcdi_await_completion() will then call efx_mcdi_poll().
	 *
	 * We need an smp_wmb() to synchronise with efx_mcdi_await_completion(),
	 * which efx_mcdi_complete_sync() provides for us.
	 */
	mcdi->mode = MCDI_MODE_POLL;

	efx_mcdi_complete_sync(mcdi);
}