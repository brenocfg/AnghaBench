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

/* Variables and functions */
 int PXA_ISA_IRQ (int /*<<< orphan*/ ) ; 
 int* zeus_isa_irqs ; 

__attribute__((used)) static inline int zeus_bit_to_irq(int bit)
{
	return zeus_isa_irqs[bit] + PXA_ISA_IRQ(0);
}