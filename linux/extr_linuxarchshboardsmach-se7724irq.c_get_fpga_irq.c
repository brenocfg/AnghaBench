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
struct fpga_irq {int /*<<< orphan*/  base; int /*<<< orphan*/  mask; int /*<<< orphan*/  mraddr; int /*<<< orphan*/  sraddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ0_BASE ; 
#define  IRQ0_IRQ 129 
 int /*<<< orphan*/  IRQ0_MASK ; 
 int /*<<< orphan*/  IRQ0_MR ; 
 int /*<<< orphan*/  IRQ0_SR ; 
 int /*<<< orphan*/  IRQ1_BASE ; 
#define  IRQ1_IRQ 128 
 int /*<<< orphan*/  IRQ1_MASK ; 
 int /*<<< orphan*/  IRQ1_MR ; 
 int /*<<< orphan*/  IRQ1_SR ; 
 int /*<<< orphan*/  IRQ2_BASE ; 
 int /*<<< orphan*/  IRQ2_MASK ; 
 int /*<<< orphan*/  IRQ2_MR ; 
 int /*<<< orphan*/  IRQ2_SR ; 

__attribute__((used)) static struct fpga_irq get_fpga_irq(unsigned int irq)
{
	struct fpga_irq set;

	switch (irq) {
	case IRQ0_IRQ:
		set.sraddr = IRQ0_SR;
		set.mraddr = IRQ0_MR;
		set.mask   = IRQ0_MASK;
		set.base   = IRQ0_BASE;
		break;
	case IRQ1_IRQ:
		set.sraddr = IRQ1_SR;
		set.mraddr = IRQ1_MR;
		set.mask   = IRQ1_MASK;
		set.base   = IRQ1_BASE;
		break;
	default:
		set.sraddr = IRQ2_SR;
		set.mraddr = IRQ2_MR;
		set.mask   = IRQ2_MASK;
		set.base   = IRQ2_BASE;
		break;
	}

	return set;
}