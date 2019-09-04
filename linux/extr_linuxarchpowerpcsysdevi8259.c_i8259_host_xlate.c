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
typedef  int u32 ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;
typedef  int irq_hw_number_t ;

/* Variables and functions */
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_NONE ; 

__attribute__((used)) static int i8259_host_xlate(struct irq_domain *h, struct device_node *ct,
			    const u32 *intspec, unsigned int intsize,
			    irq_hw_number_t *out_hwirq, unsigned int *out_flags)
{
	static unsigned char map_isa_senses[4] = {
		IRQ_TYPE_LEVEL_LOW,
		IRQ_TYPE_LEVEL_HIGH,
		IRQ_TYPE_EDGE_FALLING,
		IRQ_TYPE_EDGE_RISING,
	};

	*out_hwirq = intspec[0];
	if (intsize > 1 && intspec[1] < 4)
		*out_flags = map_isa_senses[intspec[1]];
	else
		*out_flags = IRQ_TYPE_NONE;

	return 0;
}