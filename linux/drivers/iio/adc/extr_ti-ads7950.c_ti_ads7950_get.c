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
struct ti_ads7950_state {int gpio_cmd_settings_bitmask; int cmd_settings_bitmask; int single_rx; int /*<<< orphan*/  slock; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  spi; void* single_tx; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 int TI_ADS7950_CR_GPIO_DATA ; 
 void* TI_ADS7950_MAN_CMD_SETTINGS (struct ti_ads7950_state*) ; 
 struct ti_ads7950_state* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_ads7950_get(struct gpio_chip *chip, unsigned int offset)
{
	struct ti_ads7950_state *st = gpiochip_get_data(chip);
	int ret;

	mutex_lock(&st->slock);

	/* If set as output, return the output */
	if (st->gpio_cmd_settings_bitmask & BIT(offset)) {
		ret = st->cmd_settings_bitmask & BIT(offset);
		goto out;
	}

	/* GPIO data bit sets SDO bits 12-15 to GPIO input */
	st->cmd_settings_bitmask |= TI_ADS7950_CR_GPIO_DATA;
	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		goto out;

	ret = ((st->single_rx >> 12) & BIT(offset)) ? 1 : 0;

	/* Revert back to original settings */
	st->cmd_settings_bitmask &= ~TI_ADS7950_CR_GPIO_DATA;
	st->single_tx = TI_ADS7950_MAN_CMD_SETTINGS(st);
	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		goto out;

out:
	mutex_unlock(&st->slock);

	return ret;
}