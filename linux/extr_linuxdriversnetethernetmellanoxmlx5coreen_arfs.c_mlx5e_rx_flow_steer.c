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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ protocol; scalar_t__ encapsulation; } ;
struct net_device {int dummy; } ;
struct mlx5e_arfs_tables {int /*<<< orphan*/  arfs_lock; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {struct mlx5e_arfs_tables arfs; } ;
struct mlx5e_priv {TYPE_1__ fs; } ;
struct arfs_table {int dummy; } ;
struct arfs_rule {int filter_id; int /*<<< orphan*/  arfs_work; int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 struct arfs_rule* arfs_alloc_rule (struct mlx5e_priv*,struct arfs_table*,struct sk_buff const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct arfs_rule* arfs_find_rule (struct arfs_table*,struct sk_buff const*) ; 
 int /*<<< orphan*/  arfs_get_ip_proto (struct sk_buff const*) ; 
 struct arfs_table* arfs_get_table (struct mlx5e_arfs_tables*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mlx5e_rx_flow_steer(struct net_device *dev, const struct sk_buff *skb,
			u16 rxq_index, u32 flow_id)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_arfs_tables *arfs = &priv->fs.arfs;
	struct arfs_table *arfs_t;
	struct arfs_rule *arfs_rule;

	if (skb->protocol != htons(ETH_P_IP) &&
	    skb->protocol != htons(ETH_P_IPV6))
		return -EPROTONOSUPPORT;

	if (skb->encapsulation)
		return -EPROTONOSUPPORT;

	arfs_t = arfs_get_table(arfs, arfs_get_ip_proto(skb), skb->protocol);
	if (!arfs_t)
		return -EPROTONOSUPPORT;

	spin_lock_bh(&arfs->arfs_lock);
	arfs_rule = arfs_find_rule(arfs_t, skb);
	if (arfs_rule) {
		if (arfs_rule->rxq == rxq_index) {
			spin_unlock_bh(&arfs->arfs_lock);
			return arfs_rule->filter_id;
		}
		arfs_rule->rxq = rxq_index;
	} else {
		arfs_rule = arfs_alloc_rule(priv, arfs_t, skb,
					    rxq_index, flow_id);
		if (!arfs_rule) {
			spin_unlock_bh(&arfs->arfs_lock);
			return -ENOMEM;
		}
	}
	queue_work(priv->fs.arfs.wq, &arfs_rule->arfs_work);
	spin_unlock_bh(&arfs->arfs_lock);
	return arfs_rule->filter_id;
}