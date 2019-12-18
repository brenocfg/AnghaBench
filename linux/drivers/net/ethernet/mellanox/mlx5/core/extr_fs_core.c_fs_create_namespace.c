#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct mlx5_flow_namespace {int def_miss_action; TYPE_1__ node; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct fs_prio {TYPE_3__ node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_flow_namespace* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  del_sw_ns ; 
 int /*<<< orphan*/  fs_init_namespace (struct mlx5_flow_namespace*) ; 
 struct mlx5_flow_namespace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_add_node (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  tree_init_node (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_flow_namespace *fs_create_namespace(struct fs_prio *prio,
						       int def_miss_act)
{
	struct mlx5_flow_namespace	*ns;

	ns = kzalloc(sizeof(*ns), GFP_KERNEL);
	if (!ns)
		return ERR_PTR(-ENOMEM);

	fs_init_namespace(ns);
	ns->def_miss_action = def_miss_act;
	tree_init_node(&ns->node, NULL, del_sw_ns);
	tree_add_node(&ns->node, &prio->node);
	list_add_tail(&ns->node.list, &prio->node.children);

	return ns;
}