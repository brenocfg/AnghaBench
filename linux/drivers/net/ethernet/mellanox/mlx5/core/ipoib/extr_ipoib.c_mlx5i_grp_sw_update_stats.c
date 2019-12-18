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
struct mlx5e_sw_stats {int /*<<< orphan*/  tx_queue_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  member_0; } ;
struct mlx5e_sq_stats {scalar_t__ dropped; scalar_t__ bytes; scalar_t__ packets; } ;
struct mlx5e_rq_stats {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw; } ;
struct mlx5e_priv {int max_nch; int max_opened_tc; TYPE_1__ stats; struct mlx5e_channel_stats* channel_stats; } ;
struct mlx5e_channel_stats {struct mlx5e_sq_stats* sq; struct mlx5e_rq_stats rq; } ;
typedef  int /*<<< orphan*/  s ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlx5e_sw_stats*,int) ; 

__attribute__((used)) static void mlx5i_grp_sw_update_stats(struct mlx5e_priv *priv)
{
	struct mlx5e_sw_stats s = { 0 };
	int i, j;

	for (i = 0; i < priv->max_nch; i++) {
		struct mlx5e_channel_stats *channel_stats;
		struct mlx5e_rq_stats *rq_stats;

		channel_stats = &priv->channel_stats[i];
		rq_stats = &channel_stats->rq;

		s.rx_packets += rq_stats->packets;
		s.rx_bytes   += rq_stats->bytes;

		for (j = 0; j < priv->max_opened_tc; j++) {
			struct mlx5e_sq_stats *sq_stats = &channel_stats->sq[j];

			s.tx_packets           += sq_stats->packets;
			s.tx_bytes             += sq_stats->bytes;
			s.tx_queue_dropped     += sq_stats->dropped;
		}
	}

	memcpy(&priv->stats.sw, &s, sizeof(s));
}