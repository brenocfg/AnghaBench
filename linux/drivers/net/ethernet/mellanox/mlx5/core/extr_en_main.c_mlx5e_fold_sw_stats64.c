#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mlx5e_sq_stats {scalar_t__ dropped; scalar_t__ bytes; scalar_t__ packets; } ;
struct mlx5e_rq_stats {scalar_t__ bytes; scalar_t__ packets; } ;
struct mlx5e_priv {int max_nch; int max_opened_tc; struct mlx5e_channel_stats* channel_stats; } ;
struct mlx5e_channel_stats {struct mlx5e_sq_stats* sq; struct mlx5e_rq_stats rq; struct mlx5e_rq_stats xskrq; } ;

/* Variables and functions */

void mlx5e_fold_sw_stats64(struct mlx5e_priv *priv, struct rtnl_link_stats64 *s)
{
	int i;

	for (i = 0; i < priv->max_nch; i++) {
		struct mlx5e_channel_stats *channel_stats = &priv->channel_stats[i];
		struct mlx5e_rq_stats *xskrq_stats = &channel_stats->xskrq;
		struct mlx5e_rq_stats *rq_stats = &channel_stats->rq;
		int j;

		s->rx_packets   += rq_stats->packets + xskrq_stats->packets;
		s->rx_bytes     += rq_stats->bytes + xskrq_stats->bytes;

		for (j = 0; j < priv->max_opened_tc; j++) {
			struct mlx5e_sq_stats *sq_stats = &channel_stats->sq[j];

			s->tx_packets    += sq_stats->packets;
			s->tx_bytes      += sq_stats->bytes;
			s->tx_dropped    += sq_stats->dropped;
		}
	}
}