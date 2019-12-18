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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mlx5e_sw_stats {int /*<<< orphan*/  tx_queue_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_2__ {struct mlx5e_sw_stats sw; } ;
struct mlx5e_priv {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_sw_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5e_fold_sw_stats64 (struct mlx5e_priv*,struct rtnl_link_stats64*) ; 

__attribute__((used)) static void mlx5e_rep_update_sw_counters(struct mlx5e_priv *priv)
{
	struct mlx5e_sw_stats *s = &priv->stats.sw;
	struct rtnl_link_stats64 stats64 = {};

	memset(s, 0, sizeof(*s));
	mlx5e_fold_sw_stats64(priv, &stats64);

	s->rx_packets = stats64.rx_packets;
	s->rx_bytes   = stats64.rx_bytes;
	s->tx_packets = stats64.tx_packets;
	s->tx_bytes   = stats64.tx_bytes;
	s->tx_queue_dropped = stats64.tx_dropped;
}