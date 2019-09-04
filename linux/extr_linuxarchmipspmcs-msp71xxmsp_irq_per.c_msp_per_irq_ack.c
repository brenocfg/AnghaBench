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
 int MSP_PER_INTBASE ; 
 int* PER_INT_STS_REG ; 
 int /*<<< orphan*/  mask_per_irq (struct irq_data*) ; 

__attribute__((used)) static inline void msp_per_irq_ack(struct irq_data *d)
{
	mask_per_irq(d);
	/*
	 * In the PER interrupt controller, only bits 11 and 10
	 * are write-to-clear, (SPI TX complete, SPI RX complete).
	 * It does nothing for any others.
	 */
	*PER_INT_STS_REG = (1 << (d->irq - MSP_PER_INTBASE));
}