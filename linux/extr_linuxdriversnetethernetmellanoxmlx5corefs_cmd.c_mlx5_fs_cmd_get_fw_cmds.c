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
struct mlx5_flow_cmds {int dummy; } ;

/* Variables and functions */
 struct mlx5_flow_cmds const mlx5_flow_cmds ; 

__attribute__((used)) static const struct mlx5_flow_cmds *mlx5_fs_cmd_get_fw_cmds(void)
{
	return &mlx5_flow_cmds;
}