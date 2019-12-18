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
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int datapath_caps2; } ;

/* Variables and functions */
 scalar_t__ EFX_REV_HUNT_A0 ; 
 int MC_CMD_GET_CAPABILITIES_V2_OUT_TX_MAC_TIMESTAMPING_LBN ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 

bool efx_ptp_use_mac_tx_timestamps(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	return ((efx_nic_rev(efx) >= EFX_REV_HUNT_A0) &&
		(nic_data->datapath_caps2 &
		 (1 << MC_CMD_GET_CAPABILITIES_V2_OUT_TX_MAC_TIMESTAMPING_LBN)
		));
}