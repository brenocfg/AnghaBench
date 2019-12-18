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
struct mlx5_flow_root_namespace {TYPE_1__ fs_dr_domain; } ;

/* Variables and functions */
 int mlx5dr_domain_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_cmd_dr_destroy_ns(struct mlx5_flow_root_namespace *ns)
{
	return mlx5dr_domain_destroy(ns->fs_dr_domain.dr_domain);
}