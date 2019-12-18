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
struct regulator_enable_gpio {int enable_count; int /*<<< orphan*/  gpiod; } ;
struct regulator_dev {struct regulator_enable_gpio* ena_pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int regulator_ena_gpio_ctrl(struct regulator_dev *rdev, bool enable)
{
	struct regulator_enable_gpio *pin = rdev->ena_pin;

	if (!pin)
		return -EINVAL;

	if (enable) {
		/* Enable GPIO at initial use */
		if (pin->enable_count == 0)
			gpiod_set_value_cansleep(pin->gpiod, 1);

		pin->enable_count++;
	} else {
		if (pin->enable_count > 1) {
			pin->enable_count--;
			return 0;
		}

		/* Disable GPIO if not used */
		if (pin->enable_count <= 1) {
			gpiod_set_value_cansleep(pin->gpiod, 0);
			pin->enable_count = 0;
		}
	}

	return 0;
}