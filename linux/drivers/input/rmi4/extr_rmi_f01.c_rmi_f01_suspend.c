#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  control_base_addr; } ;
struct rmi_function {int /*<<< orphan*/  dev; TYPE_2__ fd; TYPE_4__* rmi_dev; } ;
struct TYPE_7__ {int ctrl0; } ;
struct f01_data {int old_nosleep; TYPE_3__ device_control; } ;
struct TYPE_8__ {TYPE_1__* xport; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RMI_F01_CTRL0_NOSLEEP_BIT ; 
 int RMI_F01_CTRL0_SLEEP_MODE_MASK ; 
 int RMI_SLEEP_MODE_NORMAL ; 
 int RMI_SLEEP_MODE_RESERVED1 ; 
 int RMI_SLEEP_MODE_SENSOR_SLEEP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct f01_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int rmi_write (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rmi_f01_suspend(struct rmi_function *fn)
{
	struct f01_data *f01 = dev_get_drvdata(&fn->dev);
	int error;

	f01->old_nosleep =
		f01->device_control.ctrl0 & RMI_F01_CTRL0_NOSLEEP_BIT;
	f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_NOSLEEP_BIT;

	f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
	if (device_may_wakeup(fn->rmi_dev->xport->dev))
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_RESERVED1;
	else
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_SENSOR_SLEEP;

	error = rmi_write(fn->rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	if (error) {
		dev_err(&fn->dev, "Failed to write sleep mode: %d.\n", error);
		if (f01->old_nosleep)
			f01->device_control.ctrl0 |= RMI_F01_CTRL0_NOSLEEP_BIT;
		f01->device_control.ctrl0 &= ~RMI_F01_CTRL0_SLEEP_MODE_MASK;
		f01->device_control.ctrl0 |= RMI_SLEEP_MODE_NORMAL;
		return error;
	}

	return 0;
}