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
struct mlx5e_txqsq {size_t txq_ix; } ;
struct TYPE_2__ {int num; struct mlx5e_channel** c; } ;
struct mlx5e_priv {struct mlx5e_txqsq** txq2sq; TYPE_1__ channels; } ;
struct mlx5e_channel {int num_tc; struct mlx5e_txqsq* sq; } ;

/* Variables and functions */

__attribute__((used)) static void mlx5e_build_tx2sq_maps(struct mlx5e_priv *priv)
{
	struct mlx5e_channel *c;
	struct mlx5e_txqsq *sq;
	int i, tc;

	for (i = 0; i < priv->channels.num; i++) {
		c = priv->channels.c[i];
		for (tc = 0; tc < c->num_tc; tc++) {
			sq = &c->sq[tc];
			priv->txq2sq[sq->txq_ix] = sq;
		}
	}
}