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
typedef  int irq_hw_number_t ;

/* Variables and functions */
 int IRQS_PER_MBIGEN_NODE ; 
 unsigned int MBIGEN_NODE_OFFSET ; 
 int REG_MBIGEN_TYPE_OFFSET ; 
 scalar_t__ RESERVED_IRQ_PER_MBIGEN_CHIP ; 

__attribute__((used)) static inline void get_mbigen_type_reg(irq_hw_number_t hwirq,
					u32 *mask, u32 *addr)
{
	unsigned int nid, irq_ofst, ofst;

	hwirq -= RESERVED_IRQ_PER_MBIGEN_CHIP;
	nid = hwirq / IRQS_PER_MBIGEN_NODE + 1;
	irq_ofst = hwirq % IRQS_PER_MBIGEN_NODE;

	*mask = 1 << (irq_ofst % 32);
	ofst = irq_ofst / 32 * 4;

	*addr = ofst + nid * MBIGEN_NODE_OFFSET
		+ REG_MBIGEN_TYPE_OFFSET;
}