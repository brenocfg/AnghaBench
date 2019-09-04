#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  bitmap; } ;
struct mlx4_en_priv {int* tx_ring_num; int rx_ring_num; TYPE_3__* mdev; TYPE_4__ stats_bitmap; } ;
struct bitmap_iterator {int dummy; } ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_PRIV_FLAGS 130 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int MLX4_DEV_CAP_FLAG_UC_LOOPBACK ; 
 int /*<<< orphan*/  MLX4_EN_NUM_SELF_TEST ; 
 int /*<<< orphan*/  NUM_ALL_STATS ; 
 int /*<<< orphan*/  NUM_XDP_STATS ; 
 size_t TX ; 
 int /*<<< orphan*/  bitmap_iterator_count (struct bitmap_iterator*) ; 
 int /*<<< orphan*/  bitmap_iterator_init (struct bitmap_iterator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_priv_flags ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_sset_count(struct net_device *dev, int sset)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct bitmap_iterator it;

	bitmap_iterator_init(&it, priv->stats_bitmap.bitmap, NUM_ALL_STATS);

	switch (sset) {
	case ETH_SS_STATS:
		return bitmap_iterator_count(&it) +
			(priv->tx_ring_num[TX] * 2) +
			(priv->rx_ring_num * (3 + NUM_XDP_STATS));
	case ETH_SS_TEST:
		return MLX4_EN_NUM_SELF_TEST - !(priv->mdev->dev->caps.flags
					& MLX4_DEV_CAP_FLAG_UC_LOOPBACK) * 2;
	case ETH_SS_PRIV_FLAGS:
		return ARRAY_SIZE(mlx4_en_priv_flags);
	default:
		return -EOPNOTSUPP;
	}
}