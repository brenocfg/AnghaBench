#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ethtool_ts_info {int so_timestamping; int tx_types; int /*<<< orphan*/  rx_filters; int /*<<< orphan*/  phc_index; } ;
struct efx_ptp_data {TYPE_2__* efx; scalar_t__ phc_clock; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; struct efx_ef10_nic_data* nic_data; struct efx_nic* primary; } ;
struct efx_ef10_nic_data {int licensed_features; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  hwtstamp_filters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 scalar_t__ efx_ptp_use_mac_tx_timestamps (struct efx_nic*) ; 
 int /*<<< orphan*/  ptp_clock_index (scalar_t__) ; 

void efx_ptp_get_ts_info(struct efx_nic *efx, struct ethtool_ts_info *ts_info)
{
	struct efx_ptp_data *ptp = efx->ptp_data;
	struct efx_nic *primary = efx->primary;

	ASSERT_RTNL();

	if (!ptp)
		return;

	ts_info->so_timestamping |= (SOF_TIMESTAMPING_TX_HARDWARE |
				     SOF_TIMESTAMPING_RX_HARDWARE |
				     SOF_TIMESTAMPING_RAW_HARDWARE);
	/* Check licensed features.  If we don't have the license for TX
	 * timestamps, the NIC will not support them.
	 */
	if (efx_ptp_use_mac_tx_timestamps(efx)) {
		struct efx_ef10_nic_data *nic_data = efx->nic_data;

		if (!(nic_data->licensed_features &
		      (1 << LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN)))
			ts_info->so_timestamping &=
				~SOF_TIMESTAMPING_TX_HARDWARE;
	}
	if (primary && primary->ptp_data && primary->ptp_data->phc_clock)
		ts_info->phc_index =
			ptp_clock_index(primary->ptp_data->phc_clock);
	ts_info->tx_types = 1 << HWTSTAMP_TX_OFF | 1 << HWTSTAMP_TX_ON;
	ts_info->rx_filters = ptp->efx->type->hwtstamp_filters;
}