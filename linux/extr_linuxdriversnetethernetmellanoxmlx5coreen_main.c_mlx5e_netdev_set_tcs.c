#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_3__ {int num_channels; int num_tc; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;

/* Variables and functions */
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_set_tc_queue (struct net_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_netdev_set_tcs(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	int nch = priv->channels.params.num_channels;
	int ntc = priv->channels.params.num_tc;
	int tc;

	netdev_reset_tc(netdev);

	if (ntc == 1)
		return;

	netdev_set_num_tc(netdev, ntc);

	/* Map netdev TCs to offset 0
	 * We have our own UP to TXQ mapping for QoS
	 */
	for (tc = 0; tc < ntc; tc++)
		netdev_set_tc_queue(netdev, tc, nch, 0);
}