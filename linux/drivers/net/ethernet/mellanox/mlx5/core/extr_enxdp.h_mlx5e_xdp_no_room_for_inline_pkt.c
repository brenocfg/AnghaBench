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
struct mlx5e_xdp_mpwqe {scalar_t__ ds_count; scalar_t__ inline_on; } ;

/* Variables and functions */
 scalar_t__ MLX5E_XDP_INLINE_WQE_MAX_DS_CNT ; 
 scalar_t__ MLX5E_XDP_MPW_MAX_NUM_DS ; 

__attribute__((used)) static inline bool
mlx5e_xdp_no_room_for_inline_pkt(struct mlx5e_xdp_mpwqe *session)
{
	return session->inline_on &&
	       session->ds_count + MLX5E_XDP_INLINE_WQE_MAX_DS_CNT > MLX5E_XDP_MPW_MAX_NUM_DS;
}