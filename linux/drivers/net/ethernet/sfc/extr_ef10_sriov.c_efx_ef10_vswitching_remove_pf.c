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
struct efx_nic {int /*<<< orphan*/  pci_dev; TYPE_1__* net_dev; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {scalar_t__ vport_id; int /*<<< orphan*/  vport_mac; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ EVB_PORT_ID_ASSIGNED ; 
 int /*<<< orphan*/  efx_ef10_sriov_free_vf_vswitching (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ef10_vadaptor_free (struct efx_nic*,scalar_t__) ; 
 int /*<<< orphan*/  efx_ef10_vport_del_mac (struct efx_nic*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ef10_vport_free (struct efx_nic*,scalar_t__) ; 
 int /*<<< orphan*/  efx_ef10_vswitch_free (struct efx_nic*,scalar_t__) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_vfs_assigned (int /*<<< orphan*/ ) ; 

void efx_ef10_vswitching_remove_pf(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	efx_ef10_sriov_free_vf_vswitching(efx);

	efx_ef10_vadaptor_free(efx, nic_data->vport_id);

	if (nic_data->vport_id == EVB_PORT_ID_ASSIGNED)
		return; /* No vswitch was ever created */

	if (!is_zero_ether_addr(nic_data->vport_mac)) {
		efx_ef10_vport_del_mac(efx, nic_data->vport_id,
				       efx->net_dev->dev_addr);
		eth_zero_addr(nic_data->vport_mac);
	}
	efx_ef10_vport_free(efx, nic_data->vport_id);
	nic_data->vport_id = EVB_PORT_ID_ASSIGNED;

	/* Only free the vswitch if no VFs are assigned */
	if (!pci_vfs_assigned(efx->pci_dev))
		efx_ef10_vswitch_free(efx, nic_data->vport_id);
}