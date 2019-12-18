#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct TYPE_2__ {struct mlx5e_xdp_wqe_info* wqe_info; } ;
struct mlx5e_xdpsq {scalar_t__ cc; scalar_t__ pc; int /*<<< orphan*/  umem; TYPE_1__ db; int /*<<< orphan*/  wq; } ;
struct mlx5e_xdp_wqe_info {scalar_t__ num_wqebbs; } ;

/* Variables and functions */
 size_t mlx5_wq_cyc_ctr2ix (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mlx5e_free_xdpsq_desc (struct mlx5e_xdpsq*,struct mlx5e_xdp_wqe_info*,scalar_t__*,int) ; 
 int /*<<< orphan*/  xsk_umem_complete_tx (int /*<<< orphan*/ ,scalar_t__) ; 

void mlx5e_free_xdpsq_descs(struct mlx5e_xdpsq *sq)
{
	u32 xsk_frames = 0;

	while (sq->cc != sq->pc) {
		struct mlx5e_xdp_wqe_info *wi;
		u16 ci;

		ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->cc);
		wi = &sq->db.wqe_info[ci];

		sq->cc += wi->num_wqebbs;

		mlx5e_free_xdpsq_desc(sq, wi, &xsk_frames, false);
	}

	if (xsk_frames)
		xsk_umem_complete_tx(sq->umem, xsk_frames);
}