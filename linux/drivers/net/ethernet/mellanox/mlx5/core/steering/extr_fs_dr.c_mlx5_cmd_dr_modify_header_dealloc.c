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
struct TYPE_2__ {int /*<<< orphan*/  dr_action; } ;
struct mlx5_modify_hdr {TYPE_1__ action; } ;
struct mlx5_flow_root_namespace {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5dr_action_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_cmd_dr_modify_header_dealloc(struct mlx5_flow_root_namespace *ns,
					      struct mlx5_modify_hdr *modify_hdr)
{
	mlx5dr_action_destroy(modify_hdr->action.dr_action);
}