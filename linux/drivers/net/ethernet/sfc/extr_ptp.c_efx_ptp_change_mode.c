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
struct efx_nic {TYPE_1__* ptp_data; int /*<<< orphan*/  net_dev; } ;
struct TYPE_2__ {int enabled; unsigned int mode; } ;

/* Variables and functions */
 int PTP_SYNC_ATTEMPTS ; 
 int efx_ptp_start (struct efx_nic*) ; 
 int efx_ptp_stop (struct efx_nic*) ; 
 int efx_ptp_synchronize (struct efx_nic*,int) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

int efx_ptp_change_mode(struct efx_nic *efx, bool enable_wanted,
			unsigned int new_mode)
{
	if ((enable_wanted != efx->ptp_data->enabled) ||
	    (enable_wanted && (efx->ptp_data->mode != new_mode))) {
		int rc = 0;

		if (enable_wanted) {
			/* Change of mode requires disable */
			if (efx->ptp_data->enabled &&
			    (efx->ptp_data->mode != new_mode)) {
				efx->ptp_data->enabled = false;
				rc = efx_ptp_stop(efx);
				if (rc != 0)
					return rc;
			}

			/* Set new operating mode and establish
			 * baseline synchronisation, which must
			 * succeed.
			 */
			efx->ptp_data->mode = new_mode;
			if (netif_running(efx->net_dev))
				rc = efx_ptp_start(efx);
			if (rc == 0) {
				rc = efx_ptp_synchronize(efx,
							 PTP_SYNC_ATTEMPTS * 2);
				if (rc != 0)
					efx_ptp_stop(efx);
			}
		} else {
			rc = efx_ptp_stop(efx);
		}

		if (rc != 0)
			return rc;

		efx->ptp_data->enabled = enable_wanted;
	}

	return 0;
}