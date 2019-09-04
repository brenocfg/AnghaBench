#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  control_base_addr; } ;
struct rmi_function {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmi_dev; TYPE_1__ fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  doze_holdoff; int /*<<< orphan*/  wakeup_threshold; int /*<<< orphan*/  doze_interval; int /*<<< orphan*/  ctrl0; } ;
struct TYPE_5__ {scalar_t__ has_adjustable_doze_holdoff; scalar_t__ has_adjustable_doze; } ;
struct f01_data {TYPE_3__ device_control; int /*<<< orphan*/  doze_holdoff_addr; TYPE_2__ properties; int /*<<< orphan*/  wakeup_threshold_addr; int /*<<< orphan*/  doze_interval_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct f01_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rmi_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rmi_f01_config(struct rmi_function *fn)
{
	struct f01_data *f01 = dev_get_drvdata(&fn->dev);
	int error;

	error = rmi_write(fn->rmi_dev, fn->fd.control_base_addr,
			  f01->device_control.ctrl0);
	if (error) {
		dev_err(&fn->dev,
			"Failed to write device_control register: %d\n", error);
		return error;
	}

	if (f01->properties.has_adjustable_doze) {
		error = rmi_write(fn->rmi_dev, f01->doze_interval_addr,
				  f01->device_control.doze_interval);
		if (error) {
			dev_err(&fn->dev,
				"Failed to write doze interval: %d\n", error);
			return error;
		}

		error = rmi_write_block(fn->rmi_dev,
					 f01->wakeup_threshold_addr,
					 &f01->device_control.wakeup_threshold,
					 sizeof(u8));
		if (error) {
			dev_err(&fn->dev,
				"Failed to write wakeup threshold: %d\n",
				error);
			return error;
		}
	}

	if (f01->properties.has_adjustable_doze_holdoff) {
		error = rmi_write(fn->rmi_dev, f01->doze_holdoff_addr,
				  f01->device_control.doze_holdoff);
		if (error) {
			dev_err(&fn->dev,
				"Failed to write doze holdoff: %d\n", error);
			return error;
		}
	}

	return 0;
}