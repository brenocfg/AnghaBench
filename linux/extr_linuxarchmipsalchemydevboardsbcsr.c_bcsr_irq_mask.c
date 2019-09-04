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
struct irq_data {int irq; } ;

/* Variables and functions */
 scalar_t__ BCSR_REG_MASKCLR ; 
 int /*<<< orphan*/  __raw_writew (unsigned short,scalar_t__) ; 
 int bcsr_csc_base ; 
 scalar_t__ bcsr_virt ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void bcsr_irq_mask(struct irq_data *d)
{
	unsigned short v = 1 << (d->irq - bcsr_csc_base);
	__raw_writew(v, bcsr_virt + BCSR_REG_MASKCLR);
	wmb();
}