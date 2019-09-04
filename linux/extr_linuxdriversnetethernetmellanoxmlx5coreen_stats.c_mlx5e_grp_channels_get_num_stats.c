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
struct mlx5e_priv {int max_opened_tc; int /*<<< orphan*/  mdev; TYPE_1__* profile; } ;
struct TYPE_2__ {int (* max_nch ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NUM_CH_STATS ; 
 int NUM_RQ_STATS ; 
 int NUM_RQ_XDPSQ_STATS ; 
 int NUM_SQ_STATS ; 
 int NUM_XDPSQ_STATS ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_grp_channels_get_num_stats(struct mlx5e_priv *priv)
{
	int max_nch = priv->profile->max_nch(priv->mdev);

	return (NUM_RQ_STATS * max_nch) +
	       (NUM_CH_STATS * max_nch) +
	       (NUM_SQ_STATS * max_nch * priv->max_opened_tc) +
	       (NUM_RQ_XDPSQ_STATS * max_nch) +
	       (NUM_XDPSQ_STATS * max_nch);
}