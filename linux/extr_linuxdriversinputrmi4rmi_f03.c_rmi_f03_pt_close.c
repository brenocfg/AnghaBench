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
struct serio {struct f03_data* port_data; } ;
struct rmi_function {int /*<<< orphan*/  irq_mask; TYPE_2__* rmi_dev; } ;
struct f03_data {struct rmi_function* fn; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* clear_irq_bits ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rmi_f03_pt_close(struct serio *serio)
{
	struct f03_data *f03 = serio->port_data;
	struct rmi_function *fn = f03->fn;

	fn->rmi_dev->driver->clear_irq_bits(fn->rmi_dev, fn->irq_mask);
}