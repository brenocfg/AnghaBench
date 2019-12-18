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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {scalar_t__ enabled; } ;
struct mlx4_fmr {TYPE_2__ mr; TYPE_1__* mpt; scalar_t__ maps; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ start; scalar_t__ length; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ MLX4_MPT_DISABLED ; 
 scalar_t__ MLX4_MPT_EN_HW ; 
 int /*<<< orphan*/  MLX4_MPT_STATUS_HW ; 
 int /*<<< orphan*/  MLX4_MPT_STATUS_SW ; 
 int mlx4_mr_free (struct mlx4_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx4_fmr_free(struct mlx4_dev *dev, struct mlx4_fmr *fmr)
{
	int ret;

	if (fmr->maps)
		return -EBUSY;
	if (fmr->mr.enabled == MLX4_MPT_EN_HW) {
		/* In case of FMR was enabled and unmapped
		 * make sure to give ownership of MPT back to HW
		 * so HW2SW_MPT command will success.
		 */
		*(u8 *)fmr->mpt = MLX4_MPT_STATUS_SW;
		/* Make sure MPT status is visible before changing MPT fields */
		wmb();
		fmr->mpt->length = 0;
		fmr->mpt->start  = 0;
		/* Make sure MPT data is visible after changing MPT status */
		wmb();
		*(u8 *)fmr->mpt = MLX4_MPT_STATUS_HW;
		/* make sure MPT status is visible */
		wmb();
	}

	ret = mlx4_mr_free(dev, &fmr->mr);
	if (ret)
		return ret;
	fmr->mr.enabled = MLX4_MPT_DISABLED;

	return 0;
}