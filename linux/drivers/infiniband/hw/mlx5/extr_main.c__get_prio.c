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
struct mlx5_ib_flow_prio {scalar_t__ refcount; struct mlx5_flow_table* flow_table; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;

/* Variables and functions */
 struct mlx5_ib_flow_prio* ERR_CAST (struct mlx5_flow_table*) ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 struct mlx5_flow_table* mlx5_create_auto_grouped_flow_table (struct mlx5_flow_namespace*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_ib_flow_prio *_get_prio(struct mlx5_flow_namespace *ns,
					   struct mlx5_ib_flow_prio *prio,
					   int priority,
					   int num_entries, int num_groups,
					   u32 flags)
{
	struct mlx5_flow_table *ft;

	ft = mlx5_create_auto_grouped_flow_table(ns, priority,
						 num_entries,
						 num_groups,
						 0, flags);
	if (IS_ERR(ft))
		return ERR_CAST(ft);

	prio->flow_table = ft;
	prio->refcount = 0;
	return prio;
}