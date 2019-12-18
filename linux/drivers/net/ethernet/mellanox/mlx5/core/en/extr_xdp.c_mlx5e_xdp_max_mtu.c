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
struct mlx5e_xsk_param {int dummy; } ;
struct mlx5e_params {int dummy; } ;

/* Variables and functions */
 int MLX5E_HW2SW_MTU (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKB_MAX_HEAD (int) ; 
 int mlx5e_get_linear_rq_headroom (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 

int mlx5e_xdp_max_mtu(struct mlx5e_params *params, struct mlx5e_xsk_param *xsk)
{
	int hr = mlx5e_get_linear_rq_headroom(params, xsk);

	/* Let S := SKB_DATA_ALIGN(sizeof(struct skb_shared_info)).
	 * The condition checked in mlx5e_rx_is_linear_skb is:
	 *   SKB_DATA_ALIGN(sw_mtu + hard_mtu + hr) + S <= PAGE_SIZE         (1)
	 *   (Note that hw_mtu == sw_mtu + hard_mtu.)
	 * What is returned from this function is:
	 *   max_mtu = PAGE_SIZE - S - hr - hard_mtu                         (2)
	 * After assigning sw_mtu := max_mtu, the left side of (1) turns to
	 * SKB_DATA_ALIGN(PAGE_SIZE - S) + S, which is equal to PAGE_SIZE,
	 * because both PAGE_SIZE and S are already aligned. Any number greater
	 * than max_mtu would make the left side of (1) greater than PAGE_SIZE,
	 * so max_mtu is the maximum MTU allowed.
	 */

	return MLX5E_HW2SW_MTU(params, SKB_MAX_HEAD(hr));
}