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
typedef  int /*<<< orphan*/  u16 ;
struct mlx4_dev {int /*<<< orphan*/  persist; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_enter_error_state (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_internal_err_reset ; 
 int mlx4_internal_err_ret_value (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_cmd_reset_flow(struct mlx4_dev *dev, u16 op, u8 op_modifier,
			       int err)
{
	/* Only if reset flow is really active return code is based on
	  * command, otherwise current error code is returned.
	  */
	if (mlx4_internal_err_reset) {
		mlx4_enter_error_state(dev->persist);
		err = mlx4_internal_err_ret_value(dev, op, op_modifier);
	}

	return err;
}