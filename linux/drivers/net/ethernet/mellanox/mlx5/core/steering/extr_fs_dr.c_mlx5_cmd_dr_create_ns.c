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
struct TYPE_2__ {int /*<<< orphan*/  dr_domain; } ;
struct mlx5_flow_root_namespace {int /*<<< orphan*/  dev; TYPE_1__ fs_dr_domain; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5DR_DOMAIN_TYPE_FDB ; 
 int /*<<< orphan*/  mlx5_core_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx5dr_domain_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_cmd_dr_create_ns(struct mlx5_flow_root_namespace *ns)
{
	ns->fs_dr_domain.dr_domain =
		mlx5dr_domain_create(ns->dev,
				     MLX5DR_DOMAIN_TYPE_FDB);
	if (!ns->fs_dr_domain.dr_domain) {
		mlx5_core_err(ns->dev, "Failed to create dr flow namespace\n");
		return -EOPNOTSUPP;
	}
	return 0;
}