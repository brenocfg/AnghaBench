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
struct TYPE_2__ {struct fs_node* parent; } ;
struct mlx5_flow_table {int /*<<< orphan*/  num_ft; TYPE_1__ node; int /*<<< orphan*/  fgs_hash; } ;
struct fs_prio {int /*<<< orphan*/  num_ft; TYPE_1__ node; int /*<<< orphan*/  fgs_hash; } ;
struct fs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_table*,struct fs_node*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  rhltable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void del_sw_flow_table(struct fs_node *node)
{
	struct mlx5_flow_table *ft;
	struct fs_prio *prio;

	fs_get_obj(ft, node);

	rhltable_destroy(&ft->fgs_hash);
	fs_get_obj(prio, ft->node.parent);
	prio->num_ft--;
	kfree(ft);
}