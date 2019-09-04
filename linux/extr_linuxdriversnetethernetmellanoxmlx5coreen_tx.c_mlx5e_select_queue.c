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
typedef  int u16 ;
struct sk_buff {int vlan_tci; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int num_channels; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {int** channel_tc2txq; TYPE_2__ channels; } ;
typedef  int (* select_queue_fallback_t ) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int VLAN_PRIO_SHIFT ; 
 int /*<<< orphan*/  netdev_get_num_tc (struct net_device*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int reciprocal_scale (int,int) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 

u16 mlx5e_select_queue(struct net_device *dev, struct sk_buff *skb,
		       struct net_device *sb_dev,
		       select_queue_fallback_t fallback)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int channel_ix = fallback(dev, skb, NULL);
	u16 num_channels;
	int up = 0;

	if (!netdev_get_num_tc(dev))
		return channel_ix;

#ifdef CONFIG_MLX5_CORE_EN_DCB
	if (priv->dcbx_dp.trust_state == MLX5_QPTS_TRUST_DSCP)
		up = mlx5e_get_dscp_up(priv, skb);
	else
#endif
		if (skb_vlan_tag_present(skb))
			up = skb->vlan_tci >> VLAN_PRIO_SHIFT;

	/* channel_ix can be larger than num_channels since
	 * dev->num_real_tx_queues = num_channels * num_tc
	 */
	num_channels = priv->channels.params.num_channels;
	if (channel_ix >= num_channels)
		channel_ix = reciprocal_scale(channel_ix, num_channels);

	return priv->channel_tc2txq[channel_ix][up];
}