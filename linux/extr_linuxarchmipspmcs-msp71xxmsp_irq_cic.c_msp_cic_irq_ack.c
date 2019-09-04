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
 int* CIC_STS_REG ; 
 int MSP_CIC_INTBASE ; 
 int /*<<< orphan*/  mask_cic_irq (struct irq_data*) ; 

__attribute__((used)) static void msp_cic_irq_ack(struct irq_data *d)
{
	mask_cic_irq(d);
	/*
	* Only really necessary for 18, 16-14 and sometimes 3:0
	* (since these can be edge sensitive) but it doesn't
	* hurt for the others
	*/
	*CIC_STS_REG = (1 << (d->irq - MSP_CIC_INTBASE));
}