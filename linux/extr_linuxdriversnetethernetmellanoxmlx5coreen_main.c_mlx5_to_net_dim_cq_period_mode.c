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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 scalar_t__ NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE ; 
 scalar_t__ NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 

__attribute__((used)) static u8 mlx5_to_net_dim_cq_period_mode(u8 cq_period_mode)
{
	return cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE ?
		NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE :
		NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE;
}