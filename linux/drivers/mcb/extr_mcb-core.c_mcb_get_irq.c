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
struct mcb_device {struct mcb_bus* bus; } ;
struct mcb_bus {int (* get_irq ) (struct mcb_device*) ;} ;

/* Variables and functions */
 int __mcb_get_irq (struct mcb_device*) ; 
 int stub1 (struct mcb_device*) ; 

int mcb_get_irq(struct mcb_device *dev)
{
	struct mcb_bus *bus = dev->bus;

	if (bus->get_irq)
		return bus->get_irq(dev);

	return __mcb_get_irq(dev);
}