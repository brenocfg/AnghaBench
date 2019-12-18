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
struct irq_data {size_t hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int* __trigger ; 

__attribute__((used)) static int csky_mpintc_set_type(struct irq_data *d, unsigned int type)
{
	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_LEVEL_HIGH:
		__trigger[d->hwirq] = 0;
		break;
	case IRQ_TYPE_LEVEL_LOW:
		__trigger[d->hwirq] = 1;
		break;
	case IRQ_TYPE_EDGE_RISING:
		__trigger[d->hwirq] = 2;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		__trigger[d->hwirq] = 3;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}