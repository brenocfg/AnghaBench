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
struct qlcnic_esw_func_cfg {scalar_t__ vlan_id; scalar_t__ discard_tagged; } ;
struct qlcnic_adapter {scalar_t__ tx_pvid; scalar_t__ rx_pvid; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_TAGGING_ENABLED ; 

void qlcnic_set_vlan_config(struct qlcnic_adapter *adapter,
			    struct qlcnic_esw_func_cfg *esw_cfg)
{
	if (esw_cfg->discard_tagged)
		adapter->flags &= ~QLCNIC_TAGGING_ENABLED;
	else
		adapter->flags |= QLCNIC_TAGGING_ENABLED;

	if (esw_cfg->vlan_id) {
		adapter->rx_pvid = esw_cfg->vlan_id;
		adapter->tx_pvid = esw_cfg->vlan_id;
	} else {
		adapter->rx_pvid = 0;
		adapter->tx_pvid = 0;
	}
}