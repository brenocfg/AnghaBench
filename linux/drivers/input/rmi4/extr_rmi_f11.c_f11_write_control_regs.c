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
typedef  int /*<<< orphan*/  u16 ;
struct rmi_function {struct rmi_device* rmi_dev; } ;
struct rmi_device {int dummy; } ;
struct f11_2d_sensor_queries {int dummy; } ;
struct f11_2d_ctrl {int /*<<< orphan*/  ctrl0_11; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_F11_CTRL_REG_COUNT ; 
 int rmi_write_block (struct rmi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f11_write_control_regs(struct rmi_function *fn,
					struct f11_2d_sensor_queries *query,
					struct f11_2d_ctrl *ctrl,
					u16 ctrl_base_addr)
{
	struct rmi_device *rmi_dev = fn->rmi_dev;
	int error;

	error = rmi_write_block(rmi_dev, ctrl_base_addr, ctrl->ctrl0_11,
				RMI_F11_CTRL_REG_COUNT);
	if (error < 0)
		return error;

	return 0;
}