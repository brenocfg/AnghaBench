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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int C_SW0 ; 
 int /*<<< orphan*/  clear_c0_cause (int) ; 
 unsigned int dvpe () ; 
 int /*<<< orphan*/  evpe (unsigned int) ; 
 int /*<<< orphan*/  mask_mips_irq (struct irq_data*) ; 

__attribute__((used)) static void mips_mt_cpu_irq_ack(struct irq_data *d)
{
	unsigned int vpflags = dvpe();
	clear_c0_cause(C_SW0 << d->hwirq);
	evpe(vpflags);
	mask_mips_irq(d);
}