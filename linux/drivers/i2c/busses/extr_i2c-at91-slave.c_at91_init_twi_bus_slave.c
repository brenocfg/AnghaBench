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
struct at91_twi_dev {scalar_t__ smr; scalar_t__ slave_detected; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TWI_CR ; 
 scalar_t__ AT91_TWI_MSDIS ; 
 int /*<<< orphan*/  AT91_TWI_SMR ; 
 scalar_t__ AT91_TWI_SVEN ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,scalar_t__) ; 

void at91_init_twi_bus_slave(struct at91_twi_dev *dev)
{
	at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_MSDIS);
	if (dev->slave_detected && dev->smr) {
		at91_twi_write(dev, AT91_TWI_SMR, dev->smr);
		at91_twi_write(dev, AT91_TWI_CR, AT91_TWI_SVEN);
	}
}