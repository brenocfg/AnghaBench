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
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct ethsw_port_priv {int* vlans; int /*<<< orphan*/  idx; struct net_device* netdev; struct ethsw_core* ethsw_data; } ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;
struct dpsw_vlan_if_cfg {int num_ifs; int /*<<< orphan*/ * if_id; } ;

/* Variables and functions */
 size_t BRIDGE_VLAN_INFO_PVID ; 
 size_t BRIDGE_VLAN_INFO_UNTAGGED ; 
 int EEXIST ; 
 int ETHSW_VLAN_MEMBER ; 
 int ETHSW_VLAN_UNTAGGED ; 
 int dpsw_vlan_add_if (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct dpsw_vlan_if_cfg*) ; 
 int dpsw_vlan_add_if_untagged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,struct dpsw_vlan_if_cfg*) ; 
 int ethsw_port_set_pvid (struct ethsw_port_priv*,size_t) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,size_t) ; 

__attribute__((used)) static int ethsw_port_add_vlan(struct ethsw_port_priv *port_priv,
			       u16 vid, u16 flags)
{
	struct ethsw_core *ethsw = port_priv->ethsw_data;
	struct net_device *netdev = port_priv->netdev;
	struct dpsw_vlan_if_cfg vcfg;
	int err;

	if (port_priv->vlans[vid]) {
		netdev_warn(netdev, "VLAN %d already configured\n", vid);
		return -EEXIST;
	}

	vcfg.num_ifs = 1;
	vcfg.if_id[0] = port_priv->idx;
	err = dpsw_vlan_add_if(ethsw->mc_io, 0, ethsw->dpsw_handle, vid, &vcfg);
	if (err) {
		netdev_err(netdev, "dpsw_vlan_add_if err %d\n", err);
		return err;
	}

	port_priv->vlans[vid] = ETHSW_VLAN_MEMBER;

	if (flags & BRIDGE_VLAN_INFO_UNTAGGED) {
		err = dpsw_vlan_add_if_untagged(ethsw->mc_io, 0,
						ethsw->dpsw_handle,
						vid, &vcfg);
		if (err) {
			netdev_err(netdev,
				   "dpsw_vlan_add_if_untagged err %d\n", err);
			return err;
		}
		port_priv->vlans[vid] |= ETHSW_VLAN_UNTAGGED;
	}

	if (flags & BRIDGE_VLAN_INFO_PVID) {
		err = ethsw_port_set_pvid(port_priv, vid);
		if (err)
			return err;
	}

	return 0;
}