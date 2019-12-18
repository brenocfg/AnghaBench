#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_8__ {int link_info; } ;
struct TYPE_7__ {TYPE_4__ link_info; } ;
struct i40e_hw {TYPE_1__ aq; TYPE_3__ phy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct i40e_netdev_priv {TYPE_2__* vsi; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_6__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int EIO ; 
 int I40E_AQ_LINK_UP ; 
 scalar_t__ i40e_aq_set_link_restart_an (struct i40e_hw*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_nway_reset(struct net_device *netdev)
{
	/* restart autonegotiation */
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	struct i40e_hw *hw = &pf->hw;
	bool link_up = hw->phy.link_info.link_info & I40E_AQ_LINK_UP;
	i40e_status ret = 0;

	ret = i40e_aq_set_link_restart_an(hw, link_up, NULL);
	if (ret) {
		netdev_info(netdev, "link restart failed, err %s aq_err %s\n",
			    i40e_stat_str(hw, ret),
			    i40e_aq_str(hw, hw->aq.asq_last_status));
		return -EIO;
	}

	return 0;
}