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
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int create_umr_res (struct mlx5_ib_dev*) ; 

__attribute__((used)) static int mlx5_ib_stage_post_ib_reg_umr_init(struct mlx5_ib_dev *dev)
{
	return create_umr_res(dev);
}