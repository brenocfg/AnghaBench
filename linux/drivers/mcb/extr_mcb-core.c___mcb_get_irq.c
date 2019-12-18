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
struct resource {int start; } ;
struct mcb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 struct resource* mcb_get_resource (struct mcb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __mcb_get_irq(struct mcb_device *dev)
{
	struct resource *irq;

	irq = mcb_get_resource(dev, IORESOURCE_IRQ);

	return irq->start;
}