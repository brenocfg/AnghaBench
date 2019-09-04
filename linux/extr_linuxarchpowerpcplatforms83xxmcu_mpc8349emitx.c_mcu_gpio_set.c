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
struct mcu {int reg_ctrl; int /*<<< orphan*/  lock; int /*<<< orphan*/  client; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_REG_CTRL ; 
 struct mcu* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcu_gpio_set(struct gpio_chip *gc, unsigned int gpio, int val)
{
	struct mcu *mcu = gpiochip_get_data(gc);
	u8 bit = 1 << (4 + gpio);

	mutex_lock(&mcu->lock);
	if (val)
		mcu->reg_ctrl &= ~bit;
	else
		mcu->reg_ctrl |= bit;

	i2c_smbus_write_byte_data(mcu->client, MCU_REG_CTRL, mcu->reg_ctrl);
	mutex_unlock(&mcu->lock);
}