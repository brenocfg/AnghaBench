#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  cqn; } ;
struct mlx5_cqwq {scalar_t__ cc; } ;
struct TYPE_5__ {int /*<<< orphan*/  mdev; TYPE_1__ mcq; struct mlx5_cqwq wq; } ;
struct mlx5e_txqsq {TYPE_2__ cq; int /*<<< orphan*/  sqn; TYPE_3__* channel; } ;
struct mlx5_err_cqe {int /*<<< orphan*/  vendor_err_synd; int /*<<< orphan*/  syndrome; } ;
struct mlx5_cqe64 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cqe_opcode (struct mlx5_cqe64*) ; 
 int /*<<< orphan*/  mlx5_cqwq_ctr2ix (struct mlx5_cqwq*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_dump_err_cqe (int /*<<< orphan*/ ,struct mlx5_err_cqe*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_dump_error_cqe(struct mlx5e_txqsq *sq,
				 struct mlx5_err_cqe *err_cqe)
{
	struct mlx5_cqwq *wq = &sq->cq.wq;
	u32 ci;

	ci = mlx5_cqwq_ctr2ix(wq, wq->cc - 1);

	netdev_err(sq->channel->netdev,
		   "Error cqe on cqn 0x%x, ci 0x%x, sqn 0x%x, opcode 0x%x, syndrome 0x%x, vendor syndrome 0x%x\n",
		   sq->cq.mcq.cqn, ci, sq->sqn,
		   get_cqe_opcode((struct mlx5_cqe64 *)err_cqe),
		   err_cqe->syndrome, err_cqe->vendor_err_synd);
	mlx5_dump_err_cqe(sq->cq.mdev, err_cqe);
}