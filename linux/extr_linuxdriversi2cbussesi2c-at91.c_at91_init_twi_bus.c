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
struct at91_twi_dev {int /*<<< orphan*/  twi_cwgr_reg; scalar_t__ fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_CR ; 
 int /*<<< orphan*/  AT91_TWI_CWGR ; 
 int /*<<< orphan*/  AT91_TWI_FIFOEN ; 
 int /*<<< orphan*/  AT91_TWI_MSEN ; 
 int /*<<< orphan*/  AT91_TWI_SVDIS ; 
 int /*<<< orphan*/  AT91_TWI_SWRST ; 
 int /*<<< orphan*/  at91_disable_twi_interrupts (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at91_init_twi_bus(struct at91_twi_dev *dev)
{
	at91_disable_twi_interrupts(dev);
	at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_SWRST);
	/* FIFO should be enabled immediately after the software reset */
	if (dev->fifo_size)
		at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_FIFOEN);
	at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_MSEN);
	at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_SVDIS);
	at91_twi_write(dev, AT91_TWI_CWGR, dev->twi_cwgr_reg);
}