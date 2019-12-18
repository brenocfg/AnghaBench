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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct mlx5e_xsk_param {int dummy; } ;
struct mlx5e_params {int /*<<< orphan*/  sw_mtu; } ;

/* Variables and functions */
 scalar_t__ MLX5E_SW2HW_MTU (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5e_get_linear_rq_headroom (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 

u32 mlx5e_rx_get_min_frag_sz(struct mlx5e_params *params,
			     struct mlx5e_xsk_param *xsk)
{
	u32 hw_mtu = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	u16 linear_rq_headroom = mlx5e_get_linear_rq_headroom(params, xsk);

	return linear_rq_headroom + hw_mtu;
}