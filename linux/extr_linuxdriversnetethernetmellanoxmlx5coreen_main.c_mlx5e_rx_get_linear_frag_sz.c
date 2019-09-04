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
struct mlx5e_params {scalar_t__ xdp_prog; int /*<<< orphan*/  sw_mtu; } ;

/* Variables and functions */
 scalar_t__ MLX5E_SW2HW_MTU (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_RX_HEADROOM ; 
 scalar_t__ MLX5_SKB_FRAG_SZ (scalar_t__) ; 
 scalar_t__ NET_IP_ALIGN ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ XDP_PACKET_HEADROOM ; 

__attribute__((used)) static u32 mlx5e_rx_get_linear_frag_sz(struct mlx5e_params *params)
{
	u16 hw_mtu = MLX5E_SW2HW_MTU(params, params->sw_mtu);
	u16 linear_rq_headroom = params->xdp_prog ?
		XDP_PACKET_HEADROOM : MLX5_RX_HEADROOM;
	u32 frag_sz;

	linear_rq_headroom += NET_IP_ALIGN;

	frag_sz = MLX5_SKB_FRAG_SZ(linear_rq_headroom + hw_mtu);

	if (params->xdp_prog && frag_sz < PAGE_SIZE)
		frag_sz = PAGE_SIZE;

	return frag_sz;
}