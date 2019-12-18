#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct thunderx_gpio {int /*<<< orphan*/  lock; scalar_t__ register_base; int /*<<< orphan*/  od_mask; int /*<<< orphan*/  invert_mask; TYPE_1__* line_entries; } ;
struct gpio_chip {int dummy; } ;
struct TYPE_2__ {int fil_bits; } ;

/* Variables and functions */
 int EIO ; 
 int GPIO_BIT_CFG_PIN_XOR ; 
 int GPIO_BIT_CFG_TX_OD ; 
 int GPIO_BIT_CFG_TX_OE ; 
 scalar_t__ bit_cfg_reg (unsigned int) ; 
 struct thunderx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thunderx_gpio_is_gpio (struct thunderx_gpio*,unsigned int) ; 
 int /*<<< orphan*/  thunderx_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static int thunderx_gpio_dir_out(struct gpio_chip *chip, unsigned int line,
				 int value)
{
	struct thunderx_gpio *txgpio = gpiochip_get_data(chip);
	u64 bit_cfg = txgpio->line_entries[line].fil_bits | GPIO_BIT_CFG_TX_OE;

	if (!thunderx_gpio_is_gpio(txgpio, line))
		return -EIO;

	raw_spin_lock(&txgpio->lock);

	thunderx_gpio_set(chip, line, value);

	if (test_bit(line, txgpio->invert_mask))
		bit_cfg |= GPIO_BIT_CFG_PIN_XOR;

	if (test_bit(line, txgpio->od_mask))
		bit_cfg |= GPIO_BIT_CFG_TX_OD;

	writeq(bit_cfg, txgpio->register_base + bit_cfg_reg(line));

	raw_spin_unlock(&txgpio->lock);
	return 0;
}