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
struct efx_nic {int mc_bist_for_other_fn; } ;
struct efx_mcdi_iface {scalar_t__ mode; int new_epoch; int /*<<< orphan*/  iface_lock; int /*<<< orphan*/  credits; scalar_t__ resp_data_len; scalar_t__ resp_hdr_len; int /*<<< orphan*/  resprc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ MCDI_MODE_EVENTS ; 
 int /*<<< orphan*/  RESET_TYPE_MC_BIST ; 
 struct efx_mcdi_iface* efx_mcdi (struct efx_nic*) ; 
 scalar_t__ efx_mcdi_complete_sync (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  efx_mcdi_proxy_abort (struct efx_mcdi_iface*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void efx_mcdi_ev_bist(struct efx_nic *efx)
{
	struct efx_mcdi_iface *mcdi = efx_mcdi(efx);

	spin_lock(&mcdi->iface_lock);
	efx->mc_bist_for_other_fn = true;
	efx_mcdi_proxy_abort(mcdi);

	if (efx_mcdi_complete_sync(mcdi)) {
		if (mcdi->mode == MCDI_MODE_EVENTS) {
			mcdi->resprc = -EIO;
			mcdi->resp_hdr_len = 0;
			mcdi->resp_data_len = 0;
			++mcdi->credits;
		}
	}
	mcdi->new_epoch = true;
	efx_schedule_reset(efx, RESET_TYPE_MC_BIST);
	spin_unlock(&mcdi->iface_lock);
}