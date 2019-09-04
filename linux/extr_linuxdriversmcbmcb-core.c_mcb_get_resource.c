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
struct resource {int dummy; } ;
struct mcb_device {struct resource irq; struct resource mem; } ;

/* Variables and functions */
 unsigned int IORESOURCE_IRQ ; 
 unsigned int IORESOURCE_MEM ; 

struct resource *mcb_get_resource(struct mcb_device *dev, unsigned int type)
{
	if (type == IORESOURCE_MEM)
		return &dev->mem;
	else if (type == IORESOURCE_IRQ)
		return &dev->irq;
	else
		return NULL;
}