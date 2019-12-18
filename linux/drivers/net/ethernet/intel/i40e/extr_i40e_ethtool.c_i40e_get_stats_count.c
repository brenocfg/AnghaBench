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
struct net_device {int num_tx_queues; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct TYPE_2__ {int partition_id; } ;
struct i40e_pf {size_t lan_vsi; TYPE_1__ hw; struct i40e_vsi** vsi; } ;
struct i40e_netdev_priv {struct i40e_vsi* vsi; } ;

/* Variables and functions */
 int I40E_PF_STATS_LEN ; 
 int I40E_QUEUE_STATS_LEN ; 
 int I40E_VSI_STATS_LEN ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int i40e_get_stats_count(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_vsi *vsi = np->vsi;
	struct i40e_pf *pf = vsi->back;
	int stats_len;

	if (vsi == pf->vsi[pf->lan_vsi] && pf->hw.partition_id == 1)
		stats_len = I40E_PF_STATS_LEN;
	else
		stats_len = I40E_VSI_STATS_LEN;

	/* The number of stats reported for a given net_device must remain
	 * constant throughout the life of that device.
	 *
	 * This is because the API for obtaining the size, strings, and stats
	 * is spread out over three separate ethtool ioctls. There is no safe
	 * way to lock the number of stats across these calls, so we must
	 * assume that they will never change.
	 *
	 * Due to this, we report the maximum number of queues, even if not
	 * every queue is currently configured. Since we always allocate
	 * queues in pairs, we'll just use netdev->num_tx_queues * 2. This
	 * works because the num_tx_queues is set at device creation and never
	 * changes.
	 */
	stats_len += I40E_QUEUE_STATS_LEN * 2 * netdev->num_tx_queues;

	return stats_len;
}