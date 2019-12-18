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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5e_xsk_param {scalar_t__ headroom; } ;
struct mlx5e_params {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_RX_HEADROOM ; 
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 scalar_t__ XDP_PACKET_HEADROOM ; 
 scalar_t__ mlx5e_rx_is_xdp (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 

u16 mlx5e_get_linear_rq_headroom(struct mlx5e_params *params,
				 struct mlx5e_xsk_param *xsk)
{
	u16 headroom = NET_IP_ALIGN;

	if (mlx5e_rx_is_xdp(params, xsk)) {
		headroom += XDP_PACKET_HEADROOM;
		if (xsk)
			headroom += xsk->headroom;
	} else {
		headroom += MLX5_RX_HEADROOM;
	}

	return headroom;
}