#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rmi_function {int /*<<< orphan*/  irq_mask; TYPE_1__* rmi_dev; } ;
struct rmi_driver {int /*<<< orphan*/  (* clear_irq_bits ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct rmi_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_f54_config(struct rmi_function *fn)
{
	struct rmi_driver *drv = fn->rmi_dev->driver;

	drv->clear_irq_bits(fn->rmi_dev, fn->irq_mask);

	return 0;
}