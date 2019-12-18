#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_flow_steering {int dummy; } ;
struct mlx5_flow_root_namespace {TYPE_2__* dev; } ;
struct fs_node {int dummy; } ;
struct TYPE_3__ {struct mlx5_flow_steering* steering; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 struct mlx5_flow_root_namespace* find_root (struct fs_node*) ; 

__attribute__((used)) static inline struct mlx5_flow_steering *get_steering(struct fs_node *node)
{
	struct mlx5_flow_root_namespace *root = find_root(node);

	if (root)
		return root->dev->priv.steering;
	return NULL;
}