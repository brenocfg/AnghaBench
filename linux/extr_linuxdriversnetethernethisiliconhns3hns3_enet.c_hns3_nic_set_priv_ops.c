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
struct TYPE_2__ {int /*<<< orphan*/  maybe_stop_tx; int /*<<< orphan*/  fill_desc; } ;
struct hns3_nic_priv {TYPE_1__ ops; } ;

/* Variables and functions */
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  hns3_fill_desc ; 
 int /*<<< orphan*/  hns3_fill_desc_tso ; 
 int /*<<< orphan*/  hns3_nic_maybe_stop_tso ; 
 int /*<<< orphan*/  hns3_nic_maybe_stop_tx ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void hns3_nic_set_priv_ops(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);

	if ((netdev->features & NETIF_F_TSO) ||
	    (netdev->features & NETIF_F_TSO6)) {
		priv->ops.fill_desc = hns3_fill_desc_tso;
		priv->ops.maybe_stop_tx = hns3_nic_maybe_stop_tso;
	} else {
		priv->ops.fill_desc = hns3_fill_desc;
		priv->ops.maybe_stop_tx = hns3_nic_maybe_stop_tx;
	}
}