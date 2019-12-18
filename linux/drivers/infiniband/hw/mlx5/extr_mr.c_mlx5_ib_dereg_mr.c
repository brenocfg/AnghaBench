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
struct TYPE_2__ {int /*<<< orphan*/  device; } ;
struct mlx5_ib_mr {struct mlx5_ib_mr* klm_mr; TYPE_1__ ibmr; struct mlx5_ib_mr* mtt_mr; } ;
struct ib_udata {int dummy; } ;
struct ib_mr {scalar_t__ type; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ IB_MR_TYPE_INTEGRITY ; 
 int /*<<< orphan*/  dereg_mr (int /*<<< orphan*/ ,struct mlx5_ib_mr*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_mr* to_mmr (struct ib_mr*) ; 

int mlx5_ib_dereg_mr(struct ib_mr *ibmr, struct ib_udata *udata)
{
	struct mlx5_ib_mr *mmr = to_mmr(ibmr);

	if (ibmr->type == IB_MR_TYPE_INTEGRITY) {
		dereg_mr(to_mdev(mmr->mtt_mr->ibmr.device), mmr->mtt_mr);
		dereg_mr(to_mdev(mmr->klm_mr->ibmr.device), mmr->klm_mr);
	}

	dereg_mr(to_mdev(ibmr->device), mmr);

	return 0;
}