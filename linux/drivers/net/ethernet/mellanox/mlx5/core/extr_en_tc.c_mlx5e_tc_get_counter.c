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
struct mlx5e_tc_flow {TYPE_2__* nic_attr; TYPE_1__* esw_attr; } ;
struct mlx5_fc {int dummy; } ;
struct TYPE_4__ {struct mlx5_fc* counter; } ;
struct TYPE_3__ {struct mlx5_fc* counter; } ;

/* Variables and functions */
 scalar_t__ mlx5e_is_eswitch_flow (struct mlx5e_tc_flow*) ; 

__attribute__((used)) static struct mlx5_fc *mlx5e_tc_get_counter(struct mlx5e_tc_flow *flow)
{
	if (mlx5e_is_eswitch_flow(flow))
		return flow->esw_attr->counter;
	else
		return flow->nic_attr->counter;
}