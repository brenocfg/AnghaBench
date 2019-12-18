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
struct mlx5e_priv {int max_opened_tc; struct mlx5e_channel_stats* channel_stats; } ;
struct mlx5e_hv_vhca_per_ring_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct mlx5e_channel_stats {TYPE_2__* sq; TYPE_1__ rq; } ;
struct TYPE_4__ {scalar_t__ bytes; scalar_t__ packets; } ;

/* Variables and functions */

__attribute__((used)) static void
mlx5e_hv_vhca_fill_ring_stats(struct mlx5e_priv *priv, int ch,
			      struct mlx5e_hv_vhca_per_ring_stats *data)
{
	struct mlx5e_channel_stats *stats;
	int tc;

	stats = &priv->channel_stats[ch];
	data->rx_packets = stats->rq.packets;
	data->rx_bytes   = stats->rq.bytes;

	for (tc = 0; tc < priv->max_opened_tc; tc++) {
		data->tx_packets += stats->sq[tc].packets;
		data->tx_bytes   += stats->sq[tc].bytes;
	}
}