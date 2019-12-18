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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct i40e_pf {int /*<<< orphan*/  hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
typedef  scalar_t__ i40e_status ;
struct TYPE_2__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ i40e_get_link_status (int /*<<< orphan*/ *,int*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct i40e_pf*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_info (struct i40e_pf*,int /*<<< orphan*/ ,struct net_device*,char*) ; 

__attribute__((used)) static u64 i40e_link_test(struct net_device *netdev, u64 *data)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	i40e_status status;
	bool link_up = false;

	netif_info(pf, hw, netdev, "link test\n");
	status = i40e_get_link_status(&pf->hw, &link_up);
	if (status) {
		netif_err(pf, drv, netdev, "link query timed out, please retry test\n");
		*data = 1;
		return *data;
	}

	if (link_up)
		*data = 0;
	else
		*data = 1;

	return *data;
}