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
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 int ib_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlx5_ib_stage_ib_reg_init(struct mlx5_ib_dev *dev)
{
	return ib_register_device(&dev->ib_dev, NULL);
}