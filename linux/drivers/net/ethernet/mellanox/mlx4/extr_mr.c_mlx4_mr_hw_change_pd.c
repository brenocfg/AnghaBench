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
typedef  int u32 ;
struct mlx4_mpt_entry {int /*<<< orphan*/  pd_flags; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int MLX4_MPT_PD_FLAG_EN_INV ; 
 int MLX4_MPT_PD_MASK ; 
 int MLX4_MPT_PD_VF_MASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 

int mlx4_mr_hw_change_pd(struct mlx4_dev *dev, struct mlx4_mpt_entry *mpt_entry,
			 u32 pdn)
{
	u32 pd_flags = be32_to_cpu(mpt_entry->pd_flags) & ~MLX4_MPT_PD_MASK;
	/* The wrapper function will put the slave's id here */
	if (mlx4_is_mfunc(dev))
		pd_flags &= ~MLX4_MPT_PD_VF_MASK;

	mpt_entry->pd_flags = cpu_to_be32(pd_flags |
					  (pdn & MLX4_MPT_PD_MASK)
					  | MLX4_MPT_PD_FLAG_EN_INV);
	return 0;
}