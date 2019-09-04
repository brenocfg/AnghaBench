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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct macio_dev {int n_interrupts; TYPE_1__ ofdev; TYPE_2__* interrupt; } ;
struct TYPE_4__ {unsigned int start; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void macio_create_fixup_irq(struct macio_dev *dev, int index,
				   unsigned int line)
{
	unsigned int irq;

	irq = irq_create_mapping(NULL, line);
	if (!irq) {
		dev->interrupt[index].start = irq;
		dev->interrupt[index].flags = IORESOURCE_IRQ;
		dev->interrupt[index].name = dev_name(&dev->ofdev.dev);
	}
	if (dev->n_interrupts <= index)
		dev->n_interrupts = index + 1;
}