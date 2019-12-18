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
struct cbus_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk; int /*<<< orphan*/  sel; int /*<<< orphan*/  dev; int /*<<< orphan*/  dat; } ;

/* Variables and functions */
 int CBUS_ADDR_BITS ; 
 int CBUS_REG_BITS ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int cbus_receive_word (struct cbus_host*) ; 
 int /*<<< orphan*/  cbus_send_bit (struct cbus_host*,int) ; 
 int /*<<< orphan*/  cbus_send_data (struct cbus_host*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cbus_transfer(struct cbus_host *host, char rw, unsigned dev,
			 unsigned reg, unsigned data)
{
	unsigned long flags;
	int ret;

	/* We don't want interrupts disturbing our transfer */
	spin_lock_irqsave(&host->lock, flags);

	/* Reset state and start of transfer, SEL stays down during transfer */
	gpiod_set_value(host->sel, 0);

	/* Set the DAT pin to output */
	gpiod_direction_output(host->dat, 1);

	/* Send the device address */
	cbus_send_data(host, dev, CBUS_ADDR_BITS);

	/* Send the rw flag */
	cbus_send_bit(host, rw == I2C_SMBUS_READ);

	/* Send the register address */
	cbus_send_data(host, reg, CBUS_REG_BITS);

	if (rw == I2C_SMBUS_WRITE) {
		cbus_send_data(host, data, 16);
		ret = 0;
	} else {
		ret = gpiod_direction_input(host->dat);
		if (ret) {
			dev_dbg(host->dev, "failed setting direction\n");
			goto out;
		}
		gpiod_set_value(host->clk, 1);

		ret = cbus_receive_word(host);
		if (ret < 0) {
			dev_dbg(host->dev, "failed receiving data\n");
			goto out;
		}
	}

	/* Indicate end of transfer, SEL goes up until next transfer */
	gpiod_set_value(host->sel, 1);
	gpiod_set_value(host->clk, 1);
	gpiod_set_value(host->clk, 0);

out:
	spin_unlock_irqrestore(&host->lock, flags);

	return ret;
}