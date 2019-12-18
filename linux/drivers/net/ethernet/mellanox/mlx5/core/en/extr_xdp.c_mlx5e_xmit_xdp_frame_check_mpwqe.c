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
struct TYPE_3__ {int /*<<< orphan*/  wqe; } ;
struct mlx5e_xdpsq {TYPE_2__* stats; int /*<<< orphan*/  pc; int /*<<< orphan*/  cc; int /*<<< orphan*/  wq; TYPE_1__ mpwqe; } ;
struct TYPE_4__ {int /*<<< orphan*/  full; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MLX5E_XDPSQ_STOP_ROOM ; 
 int MLX5E_XDP_CHECK_OK ; 
 int MLX5E_XDP_CHECK_START_MPWQE ; 
 int /*<<< orphan*/  mlx5e_wqc_has_room_for (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_doorbell (struct mlx5e_xdpsq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5e_xmit_xdp_frame_check_mpwqe(struct mlx5e_xdpsq *sq)
{
	if (unlikely(!sq->mpwqe.wqe)) {
		if (unlikely(!mlx5e_wqc_has_room_for(&sq->wq, sq->cc, sq->pc,
						     MLX5E_XDPSQ_STOP_ROOM))) {
			/* SQ is full, ring doorbell */
			mlx5e_xmit_xdp_doorbell(sq);
			sq->stats->full++;
			return -EBUSY;
		}

		return MLX5E_XDP_CHECK_START_MPWQE;
	}

	return MLX5E_XDP_CHECK_OK;
}