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
struct mlx5e_params {scalar_t__ rq_wq_type; scalar_t__ xdp_prog; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RX_HEADROOM ; 
 scalar_t__ MLX5_WQ_TYPE_CYCLIC ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  XDP_PACKET_HEADROOM ; 
 int mlx5e_rx_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 

__attribute__((used)) static u16 mlx5e_get_rq_headroom(struct mlx5_core_dev *mdev,
				 struct mlx5e_params *params)
{
	u16 linear_rq_headroom = params->xdp_prog ?
		XDP_PACKET_HEADROOM : MLX5_RX_HEADROOM;
	bool is_linear_skb;

	linear_rq_headroom += NET_IP_ALIGN;

	is_linear_skb = (params->rq_wq_type == MLX5_WQ_TYPE_CYCLIC) ?
		mlx5e_rx_is_linear_skb(mdev, params) :
		mlx5e_rx_mpwqe_is_linear_skb(mdev, params);

	return is_linear_skb ? linear_rq_headroom : 0;
}