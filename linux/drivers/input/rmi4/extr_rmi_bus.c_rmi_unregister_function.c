#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  function_number; } ;
struct rmi_function {int num_of_irqs; int /*<<< orphan*/ * irq; TYPE_2__ dev; TYPE_1__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_DEBUG_CORE ; 
 int /*<<< orphan*/  device_del (TYPE_2__*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int /*<<< orphan*/  rmi_dbg (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

void rmi_unregister_function(struct rmi_function *fn)
{
	int i;

	rmi_dbg(RMI_DEBUG_CORE, &fn->dev, "Unregistering F%02X.\n",
			fn->fd.function_number);

	device_del(&fn->dev);
	of_node_put(fn->dev.of_node);
	put_device(&fn->dev);

	for (i = 0; i < fn->num_of_irqs; i++)
		irq_dispose_mapping(fn->irq[i]);

}