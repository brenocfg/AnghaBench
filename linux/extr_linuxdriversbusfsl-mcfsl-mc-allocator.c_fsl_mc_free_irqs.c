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
struct fsl_mc_device_irq {int /*<<< orphan*/  resource; int /*<<< orphan*/ * mc_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int irq_count; } ;
struct fsl_mc_device {struct fsl_mc_device_irq** irqs; TYPE_1__ dev; TYPE_2__ obj_desc; } ;
struct fsl_mc_bus {int /*<<< orphan*/  irq_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_mc_resource_free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_fsl_mc_bus_dprc (struct fsl_mc_device*) ; 
 struct fsl_mc_bus* to_fsl_mc_bus (struct fsl_mc_device*) ; 
 struct fsl_mc_device* to_fsl_mc_device (int /*<<< orphan*/ ) ; 

void fsl_mc_free_irqs(struct fsl_mc_device *mc_dev)
{
	int i;
	int irq_count;
	struct fsl_mc_bus *mc_bus;
	struct fsl_mc_device_irq **irqs = mc_dev->irqs;

	if (!irqs)
		return;

	irq_count = mc_dev->obj_desc.irq_count;

	if (is_fsl_mc_bus_dprc(mc_dev))
		mc_bus = to_fsl_mc_bus(mc_dev);
	else
		mc_bus = to_fsl_mc_bus(to_fsl_mc_device(mc_dev->dev.parent));

	if (!mc_bus->irq_resources)
		return;

	for (i = 0; i < irq_count; i++) {
		irqs[i]->mc_dev = NULL;
		fsl_mc_resource_free(&irqs[i]->resource);
	}

	mc_dev->irqs = NULL;
}