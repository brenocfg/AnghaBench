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
struct mlx5dr_domain {int dummy; } ;
struct TYPE_2__ {struct mlx5dr_domain* dr_domain; } ;
struct mlx5_flow_root_namespace {TYPE_1__ fs_dr_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5dr_domain_set_peer (struct mlx5dr_domain*,struct mlx5dr_domain*) ; 

__attribute__((used)) static int mlx5_cmd_dr_set_peer(struct mlx5_flow_root_namespace *ns,
				struct mlx5_flow_root_namespace *peer_ns)
{
	struct mlx5dr_domain *peer_domain = NULL;

	if (peer_ns)
		peer_domain = peer_ns->fs_dr_domain.dr_domain;
	mlx5dr_domain_set_peer(ns->fs_dr_domain.dr_domain,
			       peer_domain);
	return 0;
}