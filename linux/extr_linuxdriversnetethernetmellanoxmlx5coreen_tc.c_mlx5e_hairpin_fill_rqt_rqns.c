#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ rss_hfunc; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;
struct mlx5e_hairpin {TYPE_3__* pair; int /*<<< orphan*/  num_channels; struct mlx5e_priv* func_priv; } ;
struct TYPE_6__ {int* rqn; } ;

/* Variables and functions */
 scalar_t__ ETH_RSS_HASH_XOR ; 
 int MLX5E_INDIR_RQT_SIZE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int mlx5e_bits_invert (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_build_default_indir_rqt (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rq_num ; 

__attribute__((used)) static void mlx5e_hairpin_fill_rqt_rqns(struct mlx5e_hairpin *hp, void *rqtc)
{
	u32 indirection_rqt[MLX5E_INDIR_RQT_SIZE], rqn;
	struct mlx5e_priv *priv = hp->func_priv;
	int i, ix, sz = MLX5E_INDIR_RQT_SIZE;

	mlx5e_build_default_indir_rqt(indirection_rqt, sz,
				      hp->num_channels);

	for (i = 0; i < sz; i++) {
		ix = i;
		if (priv->channels.params.rss_hfunc == ETH_RSS_HASH_XOR)
			ix = mlx5e_bits_invert(i, ilog2(sz));
		ix = indirection_rqt[ix];
		rqn = hp->pair->rqn[ix];
		MLX5_SET(rqtc, rqtc, rq_num[i], rqn);
	}
}