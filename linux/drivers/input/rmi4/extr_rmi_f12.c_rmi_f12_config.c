#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rmi_function {int /*<<< orphan*/  dev; TYPE_1__* rmi_dev; } ;
struct rmi_driver {int /*<<< orphan*/  (* clear_irq_bits ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_irq_bits ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct rmi_2d_sensor {int /*<<< orphan*/  report_abs; } ;
struct f12_data {int /*<<< orphan*/  rel_mask; int /*<<< orphan*/  abs_mask; struct rmi_2d_sensor sensor; } ;
struct TYPE_4__ {struct rmi_driver* driver; } ;

/* Variables and functions */
 struct f12_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int rmi_f12_write_control_regs (struct rmi_function*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_f12_config(struct rmi_function *fn)
{
	struct rmi_driver *drv = fn->rmi_dev->driver;
	struct f12_data *f12 = dev_get_drvdata(&fn->dev);
	struct rmi_2d_sensor *sensor;
	int ret;

	sensor = &f12->sensor;

	if (!sensor->report_abs)
		drv->clear_irq_bits(fn->rmi_dev, f12->abs_mask);
	else
		drv->set_irq_bits(fn->rmi_dev, f12->abs_mask);

	drv->clear_irq_bits(fn->rmi_dev, f12->rel_mask);

	ret = rmi_f12_write_control_regs(fn);
	if (ret)
		dev_warn(&fn->dev,
			"Failed to write F12 control registers: %d\n", ret);

	return 0;
}