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
typedef  scalar_t__ u64 ;
struct tc_cls_matchall_offload {int /*<<< orphan*/  stats; } ;
struct rtnl_link_stats64 {scalar_t__ rx_bytes; scalar_t__ rx_packets; } ;
struct mlx5e_rep_priv {struct rtnl_link_stats64 prev_vf_vport_stats; } ;
struct TYPE_2__ {struct rtnl_link_stats64 vf_vport; } ;
struct mlx5e_priv {TYPE_1__ stats; struct mlx5e_rep_priv* ppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_stats_update (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

void mlx5e_tc_stats_matchall(struct mlx5e_priv *priv,
			     struct tc_cls_matchall_offload *ma)
{
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct rtnl_link_stats64 cur_stats;
	u64 dbytes;
	u64 dpkts;

	cur_stats = priv->stats.vf_vport;
	dpkts = cur_stats.rx_packets - rpriv->prev_vf_vport_stats.rx_packets;
	dbytes = cur_stats.rx_bytes - rpriv->prev_vf_vport_stats.rx_bytes;
	rpriv->prev_vf_vport_stats = cur_stats;
	flow_stats_update(&ma->stats, dpkts, dbytes, jiffies);
}