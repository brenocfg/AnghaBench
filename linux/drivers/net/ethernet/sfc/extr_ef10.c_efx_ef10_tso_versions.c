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
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int datapath_caps; int datapath_caps2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int MC_CMD_GET_CAPABILITIES_OUT_TX_TSO_LBN ; 
 int MC_CMD_GET_CAPABILITIES_V2_OUT_TX_TSO_V2_LBN ; 

__attribute__((used)) static u32 efx_ef10_tso_versions(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 tso_versions = 0;

	if (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_TX_TSO_LBN))
		tso_versions |= BIT(1);
	if (nic_data->datapath_caps2 &
	    (1 << MC_CMD_GET_CAPABILITIES_V2_OUT_TX_TSO_V2_LBN))
		tso_versions |= BIT(2);
	return tso_versions;
}