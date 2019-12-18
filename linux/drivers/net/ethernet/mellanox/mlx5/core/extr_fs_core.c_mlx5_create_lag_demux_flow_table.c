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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_table_attr {int prio; int /*<<< orphan*/  level; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FS_FT_OP_MOD_LAG_DEMUX ; 
 struct mlx5_flow_table* __mlx5_create_flow_table (struct mlx5_flow_namespace*,struct mlx5_flow_table_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct mlx5_flow_table*
mlx5_create_lag_demux_flow_table(struct mlx5_flow_namespace *ns,
				 int prio, u32 level)
{
	struct mlx5_flow_table_attr ft_attr = {};

	ft_attr.level = level;
	ft_attr.prio  = prio;
	return __mlx5_create_flow_table(ns, &ft_attr, FS_FT_OP_MOD_LAG_DEMUX, 0);
}