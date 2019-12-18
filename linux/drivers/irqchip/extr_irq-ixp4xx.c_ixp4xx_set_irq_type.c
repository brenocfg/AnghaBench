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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 

__attribute__((used)) static int ixp4xx_set_irq_type(struct irq_data *d, unsigned int type)
{
	/* All are level active high (asserted) here */
	if (type != IRQ_TYPE_LEVEL_HIGH)
		return -EINVAL;
	return 0;
}