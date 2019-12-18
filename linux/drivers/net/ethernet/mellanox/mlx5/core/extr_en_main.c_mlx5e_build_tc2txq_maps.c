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
struct mlx5e_priv {int max_nch; int** channel_tc2txq; TYPE_1__* profile; } ;
struct TYPE_2__ {int max_tc; } ;

/* Variables and functions */

__attribute__((used)) static void mlx5e_build_tc2txq_maps(struct mlx5e_priv *priv)
{
	int i, tc;

	for (i = 0; i < priv->max_nch; i++)
		for (tc = 0; tc < priv->profile->max_tc; tc++)
			priv->channel_tc2txq[i][tc] = i + tc * priv->max_nch;
}