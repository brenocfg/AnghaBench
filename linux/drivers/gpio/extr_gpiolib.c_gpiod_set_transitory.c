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
struct gpio_desc {TYPE_1__* gdev; int /*<<< orphan*/  flags; } ;
struct gpio_chip {int (* set_config ) (struct gpio_chip*,int,unsigned long) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct gpio_chip* chip; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FLAG_TRANSITORY ; 
 int /*<<< orphan*/  PIN_CONFIG_PERSIST_STATE ; 
 int /*<<< orphan*/  VALIDATE_DESC (struct gpio_desc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int gpio_chip_hwgpio (struct gpio_desc*) ; 
 unsigned long pinconf_to_config_packed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct gpio_chip*,int,unsigned long) ; 

int gpiod_set_transitory(struct gpio_desc *desc, bool transitory)
{
	struct gpio_chip *chip;
	unsigned long packed;
	int gpio;
	int rc;

	VALIDATE_DESC(desc);
	/*
	 * Handle FLAG_TRANSITORY first, enabling queries to gpiolib for
	 * persistence state.
	 */
	if (transitory)
		set_bit(FLAG_TRANSITORY, &desc->flags);
	else
		clear_bit(FLAG_TRANSITORY, &desc->flags);

	/* If the driver supports it, set the persistence state now */
	chip = desc->gdev->chip;
	if (!chip->set_config)
		return 0;

	packed = pinconf_to_config_packed(PIN_CONFIG_PERSIST_STATE,
					  !transitory);
	gpio = gpio_chip_hwgpio(desc);
	rc = chip->set_config(chip, gpio, packed);
	if (rc == -ENOTSUPP) {
		dev_dbg(&desc->gdev->dev, "Persistence not supported for GPIO %d\n",
				gpio);
		return 0;
	}

	return rc;
}