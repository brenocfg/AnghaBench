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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_fmr {scalar_t__ maps; scalar_t__ mpt; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_MPT_STATUS_SW ; 
 int /*<<< orphan*/  wmb () ; 

void mlx4_fmr_unmap(struct mlx4_dev *dev, struct mlx4_fmr *fmr,
		    u32 *lkey, u32 *rkey)
{
	if (!fmr->maps)
		return;

	/* To unmap: it is sufficient to take back ownership from HW */
	*(u8 *)fmr->mpt = MLX4_MPT_STATUS_SW;

	/* Make sure MPT status is visible */
	wmb();

	fmr->maps = 0;
}