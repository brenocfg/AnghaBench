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
struct mlx5_flow_table {int dummy; } ;
struct fs_node {struct fs_node* parent; int /*<<< orphan*/  list; } ;
struct fs_prio {struct fs_node node; } ;

/* Variables and functions */
 struct mlx5_flow_table* find_closest_ft_recursive (struct fs_node*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct mlx5_flow_table *find_closest_ft(struct fs_prio *prio, bool reverse)
{
	struct mlx5_flow_table *ft = NULL;
	struct fs_node *curr_node;
	struct fs_node *parent;

	parent = prio->node.parent;
	curr_node = &prio->node;
	while (!ft && parent) {
		ft = find_closest_ft_recursive(parent, &curr_node->list, reverse);
		curr_node = parent;
		parent = curr_node->parent;
	}
	return ft;
}