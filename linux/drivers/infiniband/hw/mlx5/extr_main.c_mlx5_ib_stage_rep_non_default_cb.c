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
 int /*<<< orphan*/  ib_set_device_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_dev_port_rep_ops ; 

__attribute__((used)) static int mlx5_ib_stage_rep_non_default_cb(struct mlx5_ib_dev *dev)
{
	ib_set_device_ops(&dev->ib_dev, &mlx5_ib_dev_port_rep_ops);
	return 0;
}