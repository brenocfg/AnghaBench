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
struct mlx5_flow_table {int /*<<< orphan*/  id; int /*<<< orphan*/  node; } ;
struct mlx5_flow_root_namespace {int /*<<< orphan*/  chain_lock; } ;

/* Variables and functions */
 int disconnect_flow_table (struct mlx5_flow_table*) ; 
 struct mlx5_flow_root_namespace* find_root (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ tree_remove_node (int /*<<< orphan*/ *,int) ; 

int mlx5_destroy_flow_table(struct mlx5_flow_table *ft)
{
	struct mlx5_flow_root_namespace *root = find_root(&ft->node);
	int err = 0;

	mutex_lock(&root->chain_lock);
	err = disconnect_flow_table(ft);
	if (err) {
		mutex_unlock(&root->chain_lock);
		return err;
	}
	if (tree_remove_node(&ft->node, false))
		mlx5_core_warn(get_dev(&ft->node), "Flow table %d wasn't destroyed, refcount > 1\n",
			       ft->id);
	mutex_unlock(&root->chain_lock);

	return err;
}