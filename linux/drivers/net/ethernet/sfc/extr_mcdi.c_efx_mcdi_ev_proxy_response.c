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
struct efx_nic {int dummy; } ;
struct efx_mcdi_iface {scalar_t__ state; int /*<<< orphan*/  proxy_rx_wq; int /*<<< orphan*/  proxy_rx_handle; int /*<<< orphan*/  proxy_rx_status; } ;

/* Variables and functions */
 scalar_t__ MCDI_STATE_PROXY_WAIT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_mcdi_errno (int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void efx_mcdi_ev_proxy_response(struct efx_nic *efx,
				       u32 handle, int status)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	WARN_ON(mcdi->state != MCDI_STATE_PROXY_WAIT);

	mcdi->proxy_rx_status = efx_mcdi_errno(status);
	/* Ensure the status is written before we update the handle, since the
	 * latter is used to check if we've finished.
	 */
	wmb();
	mcdi->proxy_rx_handle = handle;
	wake_up(&mcdi->proxy_rx_wq);
}