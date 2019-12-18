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
struct i2c_client {int dummy; } ;
struct htcpld_data {unsigned int nchips; scalar_t__ int_reset_gpio_lo; scalar_t__ int_reset_gpio_hi; struct htcpld_chip* chip; } ;
struct htcpld_chip {int nirqs; unsigned long cache_in; unsigned int flow_type; int irq_start; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  cache_out; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t htcpld_handler(int irq, void *dev)
{
	struct htcpld_data *htcpld = dev;
	unsigned int i;
	unsigned long flags;
	int irqpin;

	if (!htcpld) {
		pr_debug("htcpld is null in ISR\n");
		return IRQ_HANDLED;
	}

	/*
	 * For each chip, do a read of the chip and trigger any interrupts
	 * desired.  The interrupts will be triggered from LSB to MSB (i.e.
	 * bit 0 first, then bit 1, etc.)
	 *
	 * For chips that have no interrupt range specified, just skip 'em.
	 */
	for (i = 0; i < htcpld->nchips; i++) {
		struct htcpld_chip *chip = &htcpld->chip[i];
		struct i2c_client *client;
		int val;
		unsigned long uval, old_val;

		if (!chip) {
			pr_debug("chip %d is null in ISR\n", i);
			continue;
		}

		if (chip->nirqs == 0)
			continue;

		client = chip->client;
		if (!client) {
			pr_debug("client %d is null in ISR\n", i);
			continue;
		}

		/* Scan the chip */
		val = i2c_smbus_read_byte_data(client, chip->cache_out);
		if (val < 0) {
			/* Throw a warning and skip this chip */
			dev_warn(chip->dev, "Unable to read from chip: %d\n",
				 val);
			continue;
		}

		uval = (unsigned long)val;

		spin_lock_irqsave(&chip->lock, flags);

		/* Save away the old value so we can compare it */
		old_val = chip->cache_in;

		/* Write the new value */
		chip->cache_in = uval;

		spin_unlock_irqrestore(&chip->lock, flags);

		/*
		 * For each bit in the data (starting at bit 0), trigger
		 * associated interrupts.
		 */
		for (irqpin = 0; irqpin < chip->nirqs; irqpin++) {
			unsigned oldb, newb, type = chip->flow_type;

			irq = chip->irq_start + irqpin;

			/* Run the IRQ handler, but only if the bit value
			 * changed, and the proper flags are set */
			oldb = (old_val >> irqpin) & 1;
			newb = (uval >> irqpin) & 1;

			if ((!oldb && newb && (type & IRQ_TYPE_EDGE_RISING)) ||
			    (oldb && !newb && (type & IRQ_TYPE_EDGE_FALLING))) {
				pr_debug("fire IRQ %d\n", irqpin);
				generic_handle_irq(irq);
			}
		}
	}

	/*
	 * In order to continue receiving interrupts, the int_reset_gpio must
	 * be asserted.
	 */
	if (htcpld->int_reset_gpio_hi)
		gpio_set_value(htcpld->int_reset_gpio_hi, 1);
	if (htcpld->int_reset_gpio_lo)
		gpio_set_value(htcpld->int_reset_gpio_lo, 0);

	return IRQ_HANDLED;
}