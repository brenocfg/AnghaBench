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
struct net_device {int /*<<< orphan*/ * ethtool_ops; } ;
struct i40e_pf {int /*<<< orphan*/  state; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_2__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_RECOVERY_MODE ; 
 int /*<<< orphan*/  i40e_ethtool_ops ; 
 int /*<<< orphan*/  i40e_ethtool_recovery_mode_ops ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_set_ethtool_ops(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf		*pf = np->vsi->back;

	if (!test_bit(__I40E_RECOVERY_MODE, pf->state))
		netdev->ethtool_ops = &i40e_ethtool_ops;
	else
		netdev->ethtool_ops = &i40e_ethtool_recovery_mode_ops;
}