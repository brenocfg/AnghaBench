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
struct mlx5_flow_table_attr {int /*<<< orphan*/  prio; int /*<<< orphan*/  level; int /*<<< orphan*/  max_fte; } ;
struct ttc_params {struct mlx5_flow_table_attr ft_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_INNER_TTC_FT_LEVEL ; 
 int /*<<< orphan*/  MLX5E_INNER_TTC_TABLE_SIZE ; 
 int /*<<< orphan*/  MLX5E_NIC_PRIO ; 

void mlx5e_set_inner_ttc_ft_params(struct ttc_params *ttc_params)
{
	struct mlx5_flow_table_attr *ft_attr = &ttc_params->ft_attr;

	ft_attr->max_fte = MLX5E_INNER_TTC_TABLE_SIZE;
	ft_attr->level = MLX5E_INNER_TTC_FT_LEVEL;
	ft_attr->prio = MLX5E_NIC_PRIO;
}