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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {int /*<<< orphan*/  idx; struct ethsw_core* ethsw_data; struct net_device* netdev; } ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;
struct dpsw_vlan_if_cfg {int num_ifs; int /*<<< orphan*/ * if_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_VLAN_ID ; 
 int dpsw_vlan_remove_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_vlan_if_cfg*) ; 
 int dpsw_vlan_remove_if_untagged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpsw_vlan_if_cfg*) ; 
 int ethsw_port_set_pvid (struct ethsw_port_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 

__attribute__((used)) static int ethsw_port_init(struct ethsw_port_priv *port_priv, u16 port)
{
	struct net_device *netdev = port_priv->netdev;
	struct ethsw_core *ethsw = port_priv->ethsw_data;
	struct dpsw_vlan_if_cfg vcfg;
	int err;

	/* Switch starts with all ports configured to VLAN 1. Need to
	 * remove this setting to allow configuration at bridge join
	 */
	vcfg.num_ifs = 1;
	vcfg.if_id[0] = port_priv->idx;

	err = dpsw_vlan_remove_if_untagged(ethsw->mc_io, 0, ethsw->dpsw_handle,
					   DEFAULT_VLAN_ID, &vcfg);
	if (err) {
		netdev_err(netdev, "dpsw_vlan_remove_if_untagged err %d\n",
			   err);
		return err;
	}

	err = ethsw_port_set_pvid(port_priv, 0);
	if (err)
		return err;

	err = dpsw_vlan_remove_if(ethsw->mc_io, 0, ethsw->dpsw_handle,
				  DEFAULT_VLAN_ID, &vcfg);
	if (err)
		netdev_err(netdev, "dpsw_vlan_remove_if err %d\n", err);

	return err;
}