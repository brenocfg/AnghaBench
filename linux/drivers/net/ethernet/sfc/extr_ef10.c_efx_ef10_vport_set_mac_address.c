#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct efx_nic {TYPE_1__* net_dev; int /*<<< orphan*/  filter_sem; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int /*<<< orphan*/  vport_id; int /*<<< orphan*/ * vport_mac; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RESET_TYPE_DATAPATH ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_device_attach_if_not_resetting (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_device_detach_sync (struct efx_nic*) ; 
 int efx_ef10_filter_table_probe (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_ef10_filter_table_remove (struct efx_nic*) ; 
 int efx_ef10_vadaptor_alloc (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_ef10_vadaptor_free (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_ef10_vport_add_mac (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int efx_ef10_vport_del_mac (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int efx_net_open (TYPE_1__*) ; 
 int /*<<< orphan*/  efx_net_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  efx_schedule_reset (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ef10_vport_set_mac_address(struct efx_nic *efx)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	u8 mac_old[ETH_ALEN];
	int rc, rc2;

	/* Only reconfigure a PF-created vport */
	if (is_zero_ether_addr(nic_data->vport_mac))
		return 0;

	efx_device_detach_sync(efx);
	efx_net_stop(efx->net_dev);
	down_write(&efx->filter_sem);
	efx_ef10_filter_table_remove(efx);
	up_write(&efx->filter_sem);

	rc = efx_ef10_vadaptor_free(efx, nic_data->vport_id);
	if (rc)
		goto restore_filters;

	ether_addr_copy(mac_old, nic_data->vport_mac);
	rc = efx_ef10_vport_del_mac(efx, nic_data->vport_id,
				    nic_data->vport_mac);
	if (rc)
		goto restore_vadaptor;

	rc = efx_ef10_vport_add_mac(efx, nic_data->vport_id,
				    efx->net_dev->dev_addr);
	if (!rc) {
		ether_addr_copy(nic_data->vport_mac, efx->net_dev->dev_addr);
	} else {
		rc2 = efx_ef10_vport_add_mac(efx, nic_data->vport_id, mac_old);
		if (rc2) {
			/* Failed to add original MAC, so clear vport_mac */
			eth_zero_addr(nic_data->vport_mac);
			goto reset_nic;
		}
	}

restore_vadaptor:
	rc2 = efx_ef10_vadaptor_alloc(efx, nic_data->vport_id);
	if (rc2)
		goto reset_nic;
restore_filters:
	down_write(&efx->filter_sem);
	rc2 = efx_ef10_filter_table_probe(efx);
	up_write(&efx->filter_sem);
	if (rc2)
		goto reset_nic;

	rc2 = efx_net_open(efx->net_dev);
	if (rc2)
		goto reset_nic;

	efx_device_attach_if_not_resetting(efx);

	return rc;

reset_nic:
	netif_err(efx, drv, efx->net_dev,
		  "Failed to restore when changing MAC address - scheduling reset\n");
	efx_schedule_reset(efx, RESET_TYPE_DATAPATH);

	return rc ? rc : rc2;
}