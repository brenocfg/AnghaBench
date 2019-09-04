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
struct cbus_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  clk_gpio; int /*<<< orphan*/  sel_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  dat_gpio; } ;

/* Variables and functions */
 int CBUS_ADDR_BITS ; 
 int CBUS_REG_BITS ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int cbus_receive_word (struct cbus_host*) ; 
 int /*<<< orphan*/  cbus_send_bit (struct cbus_host*,int) ; 
 int /*<<< orphan*/  cbus_send_data (struct cbus_host*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
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
	gpio_set_value(host->sel_gpio, 0);

	/* Set the DAT pin to output */
	gpio_direction_output(host->dat_gpio, 1);

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
		ret = gpio_direction_input(host->dat_gpio);
		if (ret) {
			dev_dbg(host->dev, "failed setting direction\n");
			goto out;
		}
		gpio_set_value(host->clk_gpio, 1);

		ret = cbus_receive_word(host);
		if (ret < 0) {
			dev_dbg(host->dev, "failed receiving data\n");
			goto out;
		}
	}

	/* Indicate end of transfer, SEL goes up until next transfer */
	gpio_set_value(host->sel_gpio, 1);
	gpio_set_value(host->clk_gpio, 1);
	gpio_set_value(host->clk_gpio, 0);

out:
	spin_unlock_irqrestore(&host->lock, flags);

	return ret;
}