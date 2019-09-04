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
struct mlx5e_priv {int** channel_tc2txq; TYPE_1__* profile; int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int (* max_nch ) (int /*<<< orphan*/ ) ;int max_tc; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_build_tc2txq_maps(struct mlx5e_priv *priv)
{
	int max_nch = priv->profile->max_nch(priv->mdev);
	int i, tc;

	for (i = 0; i < max_nch; i++)
		for (tc = 0; tc < priv->profile->max_tc; tc++)
			priv->channel_tc2txq[i][tc] = i + tc * max_nch;
}