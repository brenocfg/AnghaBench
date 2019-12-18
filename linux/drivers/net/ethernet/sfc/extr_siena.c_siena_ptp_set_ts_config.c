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
struct hwtstamp_config {int rx_filter; int /*<<< orphan*/  tx_type; } ;
struct efx_nic {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
#define  HWTSTAMP_FILTER_NONE 134 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 133 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 132 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 131 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 130 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 129 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 128 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  MC_CMD_PTP_MODE_V1 ; 
 int /*<<< orphan*/  MC_CMD_PTP_MODE_V2 ; 
 int /*<<< orphan*/  MC_CMD_PTP_MODE_V2_ENHANCED ; 
 int efx_ptp_change_mode (struct efx_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ptp_get_mode (struct efx_nic*) ; 

__attribute__((used)) static int siena_ptp_set_ts_config(struct efx_nic *efx,
				   struct hwtstamp_config *init)
{
	int rc;

	switch (init->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		/* if TX timestamping is still requested then leave PTP on */
		return efx_ptp_change_mode(efx,
					   init->tx_type != HWTSTAMP_TX_OFF,
					   efx_ptp_get_mode(efx));
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		init->rx_filter = HWTSTAMP_FILTER_PTP_V1_L4_EVENT;
		return efx_ptp_change_mode(efx, true, MC_CMD_PTP_MODE_V1);
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		init->rx_filter = HWTSTAMP_FILTER_PTP_V2_L4_EVENT;
		rc = efx_ptp_change_mode(efx, true,
					 MC_CMD_PTP_MODE_V2_ENHANCED);
		/* bug 33070 - old versions of the firmware do not support the
		 * improved UUID filtering option. Similarly old versions of the
		 * application do not expect it to be enabled. If the firmware
		 * does not accept the enhanced mode, fall back to the standard
		 * PTP v2 UUID filtering. */
		if (rc != 0)
			rc = efx_ptp_change_mode(efx, true, MC_CMD_PTP_MODE_V2);
		return rc;
	default:
		return -ERANGE;
	}
}