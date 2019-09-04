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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_priv {int dummy; } ;
struct TYPE_2__ {int (* fill_strings ) (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int mlx5e_num_stats_grps ; 
 TYPE_1__* mlx5e_stats_grps ; 
 int stub1 (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void mlx5e_fill_stats_strings(struct mlx5e_priv *priv, u8 *data)
{
	int i, idx = 0;

	for (i = 0; i < mlx5e_num_stats_grps; i++)
		idx = mlx5e_stats_grps[i].fill_strings(priv, data, idx);
}