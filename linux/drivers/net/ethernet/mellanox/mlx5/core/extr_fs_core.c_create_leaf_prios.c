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
struct mlx5_flow_namespace {int dummy; } ;
struct init_tree_node {int num_leaf_prios; int /*<<< orphan*/  num_levels; } ;
struct fs_prio {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fs_prio*) ; 
 int PTR_ERR (struct fs_prio*) ; 
 struct fs_prio* fs_create_prio (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_leaf_prios(struct mlx5_flow_namespace *ns, int prio,
			     struct init_tree_node *prio_metadata)
{
	struct fs_prio *fs_prio;
	int i;

	for (i = 0; i < prio_metadata->num_leaf_prios; i++) {
		fs_prio = fs_create_prio(ns, prio++, prio_metadata->num_levels);
		if (IS_ERR(fs_prio))
			return PTR_ERR(fs_prio);
	}
	return 0;
}