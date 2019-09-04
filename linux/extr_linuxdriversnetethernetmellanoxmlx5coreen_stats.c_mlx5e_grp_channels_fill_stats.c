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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5e_priv {int max_opened_tc; TYPE_2__* channel_stats; int /*<<< orphan*/  mdev; TYPE_1__* profile; } ;
struct TYPE_4__ {int /*<<< orphan*/  xdpsq; int /*<<< orphan*/ * sq; int /*<<< orphan*/  rq_xdpsq; int /*<<< orphan*/  rq; int /*<<< orphan*/  ch; } ;
struct TYPE_3__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_READ_CTR64_CPU (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int NUM_CH_STATS ; 
 int NUM_RQ_STATS ; 
 int NUM_RQ_XDPSQ_STATS ; 
 int NUM_SQ_STATS ; 
 int NUM_XDPSQ_STATS ; 
 int /*<<< orphan*/  ch_stats_desc ; 
 int /*<<< orphan*/  rq_stats_desc ; 
 int /*<<< orphan*/  rq_xdpsq_stats_desc ; 
 int /*<<< orphan*/  sq_stats_desc ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdpsq_stats_desc ; 

__attribute__((used)) static int mlx5e_grp_channels_fill_stats(struct mlx5e_priv *priv, u64 *data,
					 int idx)
{
	int max_nch = priv->profile->max_nch(priv->mdev);
	int i, j, tc;

	for (i = 0; i < max_nch; i++)
		for (j = 0; j < NUM_CH_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].ch,
						     ch_stats_desc, j);

	for (i = 0; i < max_nch; i++) {
		for (j = 0; j < NUM_RQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].rq,
						     rq_stats_desc, j);
		for (j = 0; j < NUM_RQ_XDPSQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].rq_xdpsq,
						     rq_xdpsq_stats_desc, j);
	}

	for (tc = 0; tc < priv->max_opened_tc; tc++)
		for (i = 0; i < max_nch; i++)
			for (j = 0; j < NUM_SQ_STATS; j++)
				data[idx++] =
					MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].sq[tc],
							     sq_stats_desc, j);

	for (i = 0; i < max_nch; i++)
		for (j = 0; j < NUM_XDPSQ_STATS; j++)
			data[idx++] =
				MLX5E_READ_CTR64_CPU(&priv->channel_stats[i].xdpsq,
						     xdpsq_stats_desc, j);

	return idx;
}