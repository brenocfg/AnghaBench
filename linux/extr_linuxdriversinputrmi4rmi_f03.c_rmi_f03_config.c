#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rmi_function {int /*<<< orphan*/  irq_mask; TYPE_2__* rmi_dev; int /*<<< orphan*/  dev; } ;
struct f03_data {int serio_registered; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_irq_bits ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct f03_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_f03_register_pt (struct f03_data*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_f03_config(struct rmi_function *fn)
{
	struct f03_data *f03 = dev_get_drvdata(&fn->dev);
	int error;

	if (!f03->serio_registered) {
		error = rmi_f03_register_pt(f03);
		if (error)
			return error;

		f03->serio_registered = true;
	} else {
		/*
		 * We must be re-configuring the sensor, just enable
		 * interrupts for this function.
		 */
		fn->rmi_dev->driver->set_irq_bits(fn->rmi_dev, fn->irq_mask);
	}

	return 0;
}