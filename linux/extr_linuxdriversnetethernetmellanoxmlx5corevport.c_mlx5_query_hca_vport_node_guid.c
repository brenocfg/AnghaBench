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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_hca_vport_context {int /*<<< orphan*/  node_guid; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_hca_vport_context*) ; 
 struct mlx5_hca_vport_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_query_hca_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mlx5_hca_vport_context*) ; 

int mlx5_query_hca_vport_node_guid(struct mlx5_core_dev *dev,
				   u64 *node_guid)
{
	struct mlx5_hca_vport_context *rep;
	int err;

	rep = kzalloc(sizeof(*rep), GFP_KERNEL);
	if (!rep)
		return -ENOMEM;

	err = mlx5_query_hca_vport_context(dev, 0, 1, 0, rep);
	if (!err)
		*node_guid = rep->node_guid;

	kfree(rep);
	return err;
}