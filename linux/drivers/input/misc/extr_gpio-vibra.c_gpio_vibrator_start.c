#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gpio_vibrator {int vcc_on; int /*<<< orphan*/  gpio; int /*<<< orphan*/  vcc; TYPE_2__* input; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_vibrator_start(struct gpio_vibrator *vibrator)
{
	struct device *pdev = vibrator->input->dev.parent;
	int err;

	if (!vibrator->vcc_on) {
		err = regulator_enable(vibrator->vcc);
		if (err) {
			dev_err(pdev, "failed to enable regulator: %d\n", err);
			return err;
		}
		vibrator->vcc_on = true;
	}

	gpiod_set_value_cansleep(vibrator->gpio, 1);

	return 0;
}