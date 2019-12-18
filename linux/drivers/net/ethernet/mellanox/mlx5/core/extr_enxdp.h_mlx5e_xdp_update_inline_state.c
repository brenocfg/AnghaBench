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
typedef  scalar_t__ u16 ;
struct mlx5e_xdp_mpwqe {int inline_on; } ;
struct mlx5e_xdpsq {scalar_t__ xdpi_fifo_pc; scalar_t__ xdpi_fifo_cc; struct mlx5e_xdp_mpwqe mpwqe; } ;

/* Variables and functions */
 scalar_t__ MLX5E_XDP_INLINE_WATERMARK_HIGH ; 
 scalar_t__ MLX5E_XDP_INLINE_WATERMARK_LOW ; 

__attribute__((used)) static inline void mlx5e_xdp_update_inline_state(struct mlx5e_xdpsq *sq)
{
	u16 outstanding = sq->xdpi_fifo_pc - sq->xdpi_fifo_cc;
	struct mlx5e_xdp_mpwqe *session = &sq->mpwqe;

#define MLX5E_XDP_INLINE_WATERMARK_LOW	10
#define MLX5E_XDP_INLINE_WATERMARK_HIGH 128

	if (session->inline_on) {
		if (outstanding <= MLX5E_XDP_INLINE_WATERMARK_LOW)
			session->inline_on = 0;
		return;
	}

	/* inline is false */
	if (outstanding >= MLX5E_XDP_INLINE_WATERMARK_HIGH)
		session->inline_on = 1;
}