#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int features; } ;
struct TYPE_4__ {void* maybe_stop_tx; int /*<<< orphan*/  fill_desc; int /*<<< orphan*/  get_rxd_bnum; } ;
struct hns_nic_priv {TYPE_1__ ops; int /*<<< orphan*/  enet_ver; struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_3__* dev; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_tso_stats ) (struct hnae_handle*,int) ;} ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int /*<<< orphan*/  fill_desc ; 
 int /*<<< orphan*/  fill_tso_desc ; 
 int /*<<< orphan*/  fill_v2_desc ; 
 int /*<<< orphan*/  get_rx_desc_bnum ; 
 int /*<<< orphan*/  get_v2rx_desc_bnum ; 
 void* hns_nic_maybe_stop_tso ; 
 void* hns_nic_maybe_stop_tx ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct hnae_handle*,int) ; 

__attribute__((used)) static void hns_nic_set_priv_ops(struct net_device *netdev)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct hnae_handle *h = priv->ae_handle;

	if (AE_IS_VER1(priv->enet_ver)) {
		priv->ops.fill_desc = fill_desc;
		priv->ops.get_rxd_bnum = get_rx_desc_bnum;
		priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
	} else {
		priv->ops.get_rxd_bnum = get_v2rx_desc_bnum;
		if ((netdev->features & NETIF_F_TSO) ||
		    (netdev->features & NETIF_F_TSO6)) {
			priv->ops.fill_desc = fill_tso_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tso;
			/* This chip only support 7*4096 */
			netif_set_gso_max_size(netdev, 7 * 4096);
		} else {
			priv->ops.fill_desc = fill_v2_desc;
			priv->ops.maybe_stop_tx = hns_nic_maybe_stop_tx;
		}
		/* enable tso when init
		 * control tso on/off through TSE bit in bd
		 */
		h->dev->ops->set_tso_stats(h, 1);
	}
}