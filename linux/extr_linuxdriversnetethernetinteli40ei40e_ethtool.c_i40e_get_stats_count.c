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
struct net_device {int dummy; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_2__ {int partition_id; } ;
struct i40e_pf {size_t lan_vsi; TYPE_1__ hw; struct i40e_vsi** vsi; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int I40E_PF_STATS_LEN (struct net_device*) ; 
 int I40E_VSI_STATS_LEN (struct net_device*) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_stats_count(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;

	if (vsi == pf->vsi[pf->lan_vsi] && pf->hw.partition_id == 1)
		return I40E_PF_STATS_LEN(netdev);
	else
		return I40E_VSI_STATS_LEN(netdev);
}