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
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 

__attribute__((used)) static int pca954x_irq_set_type(struct irq_data *idata, unsigned int type)
{
	if ((type & IRQ_TYPE_SENSE_MASK) != IRQ_TYPE_LEVEL_LOW)
		return -EINVAL;
	return 0;
}