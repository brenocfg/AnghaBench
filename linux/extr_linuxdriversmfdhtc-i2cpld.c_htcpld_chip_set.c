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
struct htcpld_chip {int cache_out; int /*<<< orphan*/  set_val_work; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct htcpld_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void htcpld_chip_set(struct gpio_chip *chip, unsigned offset, int val)
{
	struct i2c_client *client;
	struct htcpld_chip *chip_data = gpiochip_get_data(chip);
	unsigned long flags;

	client = chip_data->client;
	if (!client)
		return;

	spin_lock_irqsave(&chip_data->lock, flags);
	if (val)
		chip_data->cache_out |= (1 << offset);
	else
		chip_data->cache_out &= ~(1 << offset);
	spin_unlock_irqrestore(&chip_data->lock, flags);

	schedule_work(&(chip_data->set_val_work));
}