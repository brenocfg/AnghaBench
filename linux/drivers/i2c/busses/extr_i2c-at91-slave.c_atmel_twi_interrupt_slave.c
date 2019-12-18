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
typedef  int /*<<< orphan*/  u8 ;
struct at91_twi_dev {int /*<<< orphan*/  slave; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int const AT91_TWI_EOSACC ; 
 int /*<<< orphan*/  AT91_TWI_IDR ; 
 int /*<<< orphan*/  AT91_TWI_IER ; 
 int /*<<< orphan*/  AT91_TWI_IMR ; 
 scalar_t__ AT91_TWI_RHR ; 
 unsigned int const AT91_TWI_RXRDY ; 
 int /*<<< orphan*/  AT91_TWI_SR ; 
 unsigned int const AT91_TWI_SVACC ; 
 unsigned int const AT91_TWI_SVREAD ; 
 scalar_t__ AT91_TWI_THR ; 
 unsigned int const AT91_TWI_TXRDY ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_PROCESSED ; 
 int /*<<< orphan*/  I2C_SLAVE_READ_REQUESTED ; 
 int /*<<< orphan*/  I2C_SLAVE_STOP ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_RECEIVED ; 
 int /*<<< orphan*/  I2C_SLAVE_WRITE_REQUESTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int const at91_twi_read (struct at91_twi_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_twi_write (struct at91_twi_dev*,int /*<<< orphan*/ ,unsigned int const) ; 
 int /*<<< orphan*/  i2c_slave_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readb_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writeb_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t atmel_twi_interrupt_slave(int irq, void *dev_id)
{
	struct at91_twi_dev *dev = dev_id;
	const unsigned status = at91_twi_read(dev, AT91_TWI_SR);
	const unsigned irqstatus = status & at91_twi_read(dev, AT91_TWI_IMR);
	u8 value;

	if (!irqstatus)
		return IRQ_NONE;

	/* slave address has been detected on I2C bus */
	if (irqstatus & AT91_TWI_SVACC) {
		if (status & AT91_TWI_SVREAD) {
			i2c_slave_event(dev->slave,
					I2C_SLAVE_READ_REQUESTED, &value);
			writeb_relaxed(value, dev->base + AT91_TWI_THR);
			at91_twi_write(dev, AT91_TWI_IER,
				       AT91_TWI_TXRDY | AT91_TWI_EOSACC);
		} else {
			i2c_slave_event(dev->slave,
					I2C_SLAVE_WRITE_REQUESTED, &value);
			at91_twi_write(dev, AT91_TWI_IER,
				       AT91_TWI_RXRDY | AT91_TWI_EOSACC);
		}
		at91_twi_write(dev, AT91_TWI_IDR, AT91_TWI_SVACC);
	}

	/* byte transmitted to remote master */
	if (irqstatus & AT91_TWI_TXRDY) {
		i2c_slave_event(dev->slave, I2C_SLAVE_READ_PROCESSED, &value);
		writeb_relaxed(value, dev->base + AT91_TWI_THR);
	}

	/* byte received from remote master */
	if (irqstatus & AT91_TWI_RXRDY) {
		value = readb_relaxed(dev->base + AT91_TWI_RHR);
		i2c_slave_event(dev->slave, I2C_SLAVE_WRITE_RECEIVED, &value);
	}

	/* master sent stop */
	if (irqstatus & AT91_TWI_EOSACC) {
		at91_twi_write(dev, AT91_TWI_IDR,
			       AT91_TWI_TXRDY | AT91_TWI_RXRDY | AT91_TWI_EOSACC);
		at91_twi_write(dev, AT91_TWI_IER, AT91_TWI_SVACC);
		i2c_slave_event(dev->slave, I2C_SLAVE_STOP, &value);
	}

	return IRQ_HANDLED;
}