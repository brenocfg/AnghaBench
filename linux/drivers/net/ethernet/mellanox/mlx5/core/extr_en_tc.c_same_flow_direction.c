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
struct mlx5e_tc_flow {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGRESS ; 
 int /*<<< orphan*/  INGRESS ; 
 int MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
 int flow_flag_test (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool same_flow_direction(struct mlx5e_tc_flow *flow, int flags)
{
	bool dir_ingress = !!(flags & MLX5_TC_FLAG(INGRESS));
	bool dir_egress = !!(flags & MLX5_TC_FLAG(EGRESS));

	return flow_flag_test(flow, INGRESS) == dir_ingress &&
		flow_flag_test(flow, EGRESS) == dir_egress;
}