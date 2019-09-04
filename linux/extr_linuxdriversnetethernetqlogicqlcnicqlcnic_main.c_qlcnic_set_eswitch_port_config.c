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
struct qlcnic_esw_func_cfg {int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {int flags; TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int EIO ; 
 int QLCNIC_ESWITCH_ENABLED ; 
 scalar_t__ qlcnic_get_eswitch_port_config (struct qlcnic_adapter*,struct qlcnic_esw_func_cfg*) ; 
 int /*<<< orphan*/  qlcnic_set_eswitch_port_features (struct qlcnic_adapter*,struct qlcnic_esw_func_cfg*) ; 
 int /*<<< orphan*/  qlcnic_set_netdev_features (struct qlcnic_adapter*,struct qlcnic_esw_func_cfg*) ; 
 int /*<<< orphan*/  qlcnic_set_vlan_config (struct qlcnic_adapter*,struct qlcnic_esw_func_cfg*) ; 

int qlcnic_set_eswitch_port_config(struct qlcnic_adapter *adapter)
{
	struct qlcnic_esw_func_cfg esw_cfg;

	if (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		return 0;

	esw_cfg.pci_func = adapter->ahw->pci_func;
	if (qlcnic_get_eswitch_port_config(adapter, &esw_cfg))
			return -EIO;
	qlcnic_set_vlan_config(adapter, &esw_cfg);
	qlcnic_set_eswitch_port_features(adapter, &esw_cfg);
	qlcnic_set_netdev_features(adapter, &esw_cfg);

	return 0;
}