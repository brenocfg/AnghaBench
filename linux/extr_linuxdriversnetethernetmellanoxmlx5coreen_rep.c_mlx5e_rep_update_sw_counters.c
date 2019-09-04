#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_sw_stats {int /*<<< orphan*/  tx_queue_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct mlx5e_sq_stats {scalar_t__ dropped; scalar_t__ bytes; scalar_t__ packets; } ;
struct mlx5e_rq_stats {scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_8__ {int num_tc; } ;
struct TYPE_9__ {int num; TYPE_3__ params; struct mlx5e_channel** c; } ;
struct TYPE_6__ {struct mlx5e_sw_stats sw; } ;
struct mlx5e_priv {TYPE_4__ channels; TYPE_1__ stats; } ;
struct TYPE_7__ {struct mlx5e_rq_stats* stats; } ;
struct mlx5e_channel {TYPE_5__* sq; TYPE_2__ rq; } ;
struct TYPE_10__ {struct mlx5e_sq_stats* stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mlx5e_sw_stats*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx5e_rep_update_sw_counters(struct mlx5e_priv *priv)
{
	struct mlx5e_sw_stats *s = &priv->stats.sw;
	struct mlx5e_rq_stats *rq_stats;
	struct mlx5e_sq_stats *sq_stats;
	int i, j;

	memset(s, 0, sizeof(*s));
	for (i = 0; i < priv->channels.num; i++) {
		struct mlx5e_channel *c = priv->channels.c[i];

		rq_stats = c->rq.stats;

		s->rx_packets	+= rq_stats->packets;
		s->rx_bytes	+= rq_stats->bytes;

		for (j = 0; j < priv->channels.params.num_tc; j++) {
			sq_stats = c->sq[j].stats;

			s->tx_packets		+= sq_stats->packets;
			s->tx_bytes		+= sq_stats->bytes;
			s->tx_queue_dropped	+= sq_stats->dropped;
		}
	}
}