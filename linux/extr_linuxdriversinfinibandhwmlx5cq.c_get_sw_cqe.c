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
struct TYPE_3__ {int cqe; } ;
struct TYPE_4__ {int cqe_sz; } ;
struct mlx5_ib_cq {TYPE_1__ ibcq; TYPE_2__ mcq; } ;
struct mlx5_cqe64 {int op_own; } ;

/* Variables and functions */
 int MLX5_CQE_INVALID ; 
 int MLX5_CQE_OWNER_MASK ; 
 void* get_cqe (struct mlx5_ib_cq*,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void *get_sw_cqe(struct mlx5_ib_cq *cq, int n)
{
	void *cqe = get_cqe(cq, n & cq->ibcq.cqe);
	struct mlx5_cqe64 *cqe64;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	if (likely((cqe64->op_own) >> 4 != MLX5_CQE_INVALID) &&
	    !((cqe64->op_own & MLX5_CQE_OWNER_MASK) ^ !!(n & (cq->ibcq.cqe + 1)))) {
		return cqe;
	} else {
		return NULL;
	}
}