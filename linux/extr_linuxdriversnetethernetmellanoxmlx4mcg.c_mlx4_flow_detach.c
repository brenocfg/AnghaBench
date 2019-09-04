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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int mlx4_QP_FLOW_STEERING_DETACH (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int /*<<< orphan*/ ) ; 

int mlx4_flow_detach(struct mlx4_dev *dev, u64 reg_id)
{
	int err;

	err = mlx4_QP_FLOW_STEERING_DETACH(dev, reg_id);
	if (err)
		mlx4_err(dev, "Fail to detach network rule. registration id = 0x%llx\n",
			 reg_id);
	return err;
}