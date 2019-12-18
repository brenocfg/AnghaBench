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
struct net_device {int features; } ;
struct i40e_vsi {scalar_t__ macvlan_cnt; struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; scalar_t__ num_cloud_filters; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I40E_PF_RESET_FLAG ; 
 int NETIF_F_HW_L2FW_DOFFLOAD ; 
 int NETIF_F_HW_TC ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_clear_rss_lut (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_del_all_macvlans (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_do_reset (struct i40e_pf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_pf_config_rss (struct i40e_pf*) ; 
 int i40e_set_ntuple (struct i40e_pf*,int) ; 
 int /*<<< orphan*/  i40e_vlan_stripping_disable (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vlan_stripping_enable (struct i40e_vsi*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_set_features(struct net_device *netdev,
			     netdev_features_t features)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	bool need_reset;

	if (features & NETIF_F_RXHASH && !(netdev->features & NETIF_F_RXHASH))
		i40e_pf_config_rss(pf);
	else if (!(features & NETIF_F_RXHASH) &&
		 netdev->features & NETIF_F_RXHASH)
		i40e_clear_rss_lut(vsi);

	if (features & NETIF_F_HW_VLAN_CTAG_RX)
		i40e_vlan_stripping_enable(vsi);
	else
		i40e_vlan_stripping_disable(vsi);

	if (!(features & NETIF_F_HW_TC) && pf->num_cloud_filters) {
		dev_err(&pf->pdev->dev,
			"Offloaded tc filters active, can't turn hw_tc_offload off");
		return -EINVAL;
	}

	if (!(features & NETIF_F_HW_L2FW_DOFFLOAD) && vsi->macvlan_cnt)
		i40e_del_all_macvlans(vsi);

	need_reset = i40e_set_ntuple(pf, features);

	if (need_reset)
		i40e_do_reset(pf, I40E_PF_RESET_FLAG, true);

	return 0;
}