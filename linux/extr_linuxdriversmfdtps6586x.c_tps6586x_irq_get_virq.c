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
struct tps6586x {int /*<<< orphan*/  irq_domain; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tps6586x* dev_to_tps6586x (struct device*) ; 
 int irq_create_mapping (int /*<<< orphan*/ ,int) ; 

int tps6586x_irq_get_virq(struct device *dev, int irq)
{
	struct tps6586x *tps6586x = dev_to_tps6586x(dev);

	return irq_create_mapping(tps6586x->irq_domain, irq);
}