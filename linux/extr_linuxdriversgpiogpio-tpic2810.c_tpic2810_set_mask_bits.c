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
typedef  int u8 ;
struct tpic2810 {int buffer; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPIC2810_WS_COMMAND ; 
 struct tpic2810* gpiochip_get_data (struct gpio_chip*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tpic2810_set_mask_bits(struct gpio_chip *chip, u8 mask, u8 bits)
{
	struct tpic2810 *gpio = gpiochip_get_data(chip);
	u8 buffer;
	int err;

	mutex_lock(&gpio->lock);

	buffer = gpio->buffer & ~mask;
	buffer |= (mask & bits);

	err = i2c_smbus_write_byte_data(gpio->client, TPIC2810_WS_COMMAND,
					buffer);
	if (!err)
		gpio->buffer = buffer;

	mutex_unlock(&gpio->lock);
}