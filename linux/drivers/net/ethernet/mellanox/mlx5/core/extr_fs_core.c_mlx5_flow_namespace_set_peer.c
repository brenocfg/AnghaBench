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
struct mlx5_flow_root_namespace {scalar_t__ mode; TYPE_1__* cmds; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* set_peer ) (struct mlx5_flow_root_namespace*,struct mlx5_flow_root_namespace*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx5_core_err (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct mlx5_flow_root_namespace*,struct mlx5_flow_root_namespace*) ; 

int mlx5_flow_namespace_set_peer(struct mlx5_flow_root_namespace *ns,
				 struct mlx5_flow_root_namespace *peer_ns)
{
	if (peer_ns && ns->mode != peer_ns->mode) {
		mlx5_core_err(ns->dev,
			      "Can't peer namespace of different steering mode\n");
		return -EINVAL;
	}

	return ns->cmds->set_peer(ns, peer_ns);
}