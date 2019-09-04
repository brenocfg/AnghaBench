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
typedef  void* u32 ;
struct mlx5_flow_table_attr {int max_fte; int prio; void* flags; void* level; } ;
struct TYPE_2__ {int active; int required_groups; } ;
struct mlx5_flow_table {TYPE_1__ autogroup; } ;
struct mlx5_flow_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlx5_flow_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 struct mlx5_flow_table* mlx5_create_flow_table (struct mlx5_flow_namespace*,struct mlx5_flow_table_attr*) ; 

struct mlx5_flow_table*
mlx5_create_auto_grouped_flow_table(struct mlx5_flow_namespace *ns,
				    int prio,
				    int num_flow_table_entries,
				    int max_num_groups,
				    u32 level,
				    u32 flags)
{
	struct mlx5_flow_table_attr ft_attr = {};
	struct mlx5_flow_table *ft;

	if (max_num_groups > num_flow_table_entries)
		return ERR_PTR(-EINVAL);

	ft_attr.max_fte = num_flow_table_entries;
	ft_attr.prio    = prio;
	ft_attr.level   = level;
	ft_attr.flags   = flags;

	ft = mlx5_create_flow_table(ns, &ft_attr);
	if (IS_ERR(ft))
		return ft;

	ft->autogroup.active = true;
	ft->autogroup.required_groups = max_num_groups;

	return ft;
}