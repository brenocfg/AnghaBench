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
struct at91_twi_dev {scalar_t__ slave_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_CR ; 
 int /*<<< orphan*/  AT91_TWI_SWRST ; 
 int /*<<< orphan*/  at91_disable_twi_interrupts (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_init_twi_bus_master (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_init_twi_bus_slave (struct at91_twi_dev*) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void at91_init_twi_bus(struct at91_twi_dev *dev)
{
	at91_disable_twi_interrupts(dev);
	at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_SWRST);
	if (dev->slave_detected)
		at91_init_twi_bus_slave(dev);
	else
		at91_init_twi_bus_master(dev);
}