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
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_en_stats_bitmap {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  mutex; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int MLX4_FIND_NETDEV_STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_ALL_STATS ; 
 scalar_t__ NUM_FLOW_STATS ; 
 int NUM_MAIN_STATS ; 
 int NUM_PF_STATS ; 
 int NUM_PHY_STATS ; 
 int NUM_PKT_STATS ; 
 int NUM_PORT_STATS ; 
 int NUM_XDP_STATS ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_update_pfc_stats_bitmap (struct mlx4_dev*,struct mlx4_en_stats_bitmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_dropped ; 
 int /*<<< orphan*/  rx_packets ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_dropped ; 
 int /*<<< orphan*/  tx_packets ; 

void mlx4_en_set_stats_bitmap(struct mlx4_dev *dev,
			      struct mlx4_en_stats_bitmap *stats_bitmap,
			      u8 rx_ppp, u8 rx_pause,
			      u8 tx_ppp, u8 tx_pause)
{
	int last_i = 0;

	mutex_init(&stats_bitmap->mutex);
	bitmap_zero(stats_bitmap->bitmap, NUM_ALL_STATS);

	if (mlx4_is_slave(dev)) {
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_packets), 1);
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_packets), 1);
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_bytes), 1);
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_bytes), 1);
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(rx_dropped), 1);
		bitmap_set(stats_bitmap->bitmap, last_i +
					 MLX4_FIND_NETDEV_STAT(tx_dropped), 1);
	} else {
		bitmap_set(stats_bitmap->bitmap, last_i, NUM_MAIN_STATS);
	}
	last_i += NUM_MAIN_STATS;

	bitmap_set(stats_bitmap->bitmap, last_i, NUM_PORT_STATS);
	last_i += NUM_PORT_STATS;

	if (mlx4_is_master(dev))
		bitmap_set(stats_bitmap->bitmap, last_i,
			   NUM_PF_STATS);
	last_i += NUM_PF_STATS;

	mlx4_en_update_pfc_stats_bitmap(dev, stats_bitmap,
					rx_ppp, rx_pause,
					tx_ppp, tx_pause);
	last_i += NUM_FLOW_STATS;

	if (!mlx4_is_slave(dev))
		bitmap_set(stats_bitmap->bitmap, last_i, NUM_PKT_STATS);
	last_i += NUM_PKT_STATS;

	bitmap_set(stats_bitmap->bitmap, last_i, NUM_XDP_STATS);
	last_i += NUM_XDP_STATS;

	if (!mlx4_is_slave(dev))
		bitmap_set(stats_bitmap->bitmap, last_i, NUM_PHY_STATS);
	last_i += NUM_PHY_STATS;
}