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
struct mlx5_wqe_srq_next_seg {int dummy; } ;
struct TYPE_2__ {int wqe_shift; } ;
struct mlx5_ib_srq {TYPE_1__ msrq; } ;
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*) ; 

__attribute__((used)) static int mlx5_ib_mr_responder_pfault_handler_srq(struct mlx5_ib_dev *dev,
						   struct mlx5_ib_srq *srq,
						   void **wqe, void **wqe_end,
						   int wqe_length)
{
	int wqe_size = 1 << srq->msrq.wqe_shift;

	if (wqe_size > wqe_length) {
		mlx5_ib_err(dev, "Couldn't read all of the receive WQE's content\n");
		return -EFAULT;
	}

	*wqe_end = *wqe + wqe_size;
	*wqe += sizeof(struct mlx5_wqe_srq_next_seg);

	return 0;
}