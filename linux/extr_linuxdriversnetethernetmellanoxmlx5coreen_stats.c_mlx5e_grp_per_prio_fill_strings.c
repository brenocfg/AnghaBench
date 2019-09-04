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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int mlx5e_grp_per_prio_pfc_fill_strings (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ; 
 int mlx5e_grp_per_prio_traffic_fill_strings (struct mlx5e_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mlx5e_grp_per_prio_fill_strings(struct mlx5e_priv *priv, u8 *data,
					   int idx)
{
	idx = mlx5e_grp_per_prio_traffic_fill_strings(priv, data, idx);
	idx = mlx5e_grp_per_prio_pfc_fill_strings(priv, data, idx);
	return idx;
}