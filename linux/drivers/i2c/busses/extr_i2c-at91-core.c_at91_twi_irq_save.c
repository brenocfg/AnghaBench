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
struct at91_twi_dev {int imr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_IMR ; 
 int AT91_TWI_INT_MASK ; 
 int /*<<< orphan*/  at91_disable_twi_interrupts (struct at91_twi_dev*) ; 
 int at91_twi_read (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 

void at91_twi_irq_save(struct at91_twi_dev *dev)
{
	dev->imr = at91_twi_read(dev, AT91_TWI_IMR) & AT91_TWI_INT_MASK;
	at91_disable_twi_interrupts(dev);
}