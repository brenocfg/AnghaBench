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
struct TYPE_6__ {int num; struct mlx5e_channel** c; } ;
struct mlx5e_priv {TYPE_1__ channels; struct mlx5_core_dev* mdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  mcq; } ;
struct TYPE_10__ {TYPE_4__ cq; } ;
struct mlx5e_channel {int num_tc; TYPE_5__ rq; TYPE_3__* sq; } ;
struct mlx5_core_dev {int dummy; } ;
struct ethtool_coalesce {int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;
struct TYPE_7__ {int /*<<< orphan*/  mcq; } ;
struct TYPE_8__ {TYPE_2__ cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_modify_cq_moderation (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5e_set_priv_channels_coalesce(struct mlx5e_priv *priv, struct ethtool_coalesce *coal)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	int tc;
	int i;

	for (i = 0; i < priv->channels.num; ++i) {
		struct mlx5e_channel *c = priv->channels.c[i];

		for (tc = 0; tc < c->num_tc; tc++) {
			mlx5_core_modify_cq_moderation(mdev,
						&c->sq[tc].cq.mcq,
						coal->tx_coalesce_usecs,
						coal->tx_max_coalesced_frames);
		}

		mlx5_core_modify_cq_moderation(mdev, &c->rq.cq.mcq,
					       coal->rx_coalesce_usecs,
					       coal->rx_max_coalesced_frames);
	}
}