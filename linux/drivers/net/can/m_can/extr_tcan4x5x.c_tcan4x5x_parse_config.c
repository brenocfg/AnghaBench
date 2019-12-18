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
struct tcan4x5x_priv {int /*<<< orphan*/  power; int /*<<< orphan*/ * device_state_gpio; int /*<<< orphan*/ * reset_gpio; int /*<<< orphan*/ * device_wake_gpio; } ;
struct m_can_classdev {int /*<<< orphan*/  dev; struct tcan4x5x_priv* device_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get_optional (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tcan4x5x_parse_config(struct m_can_classdev *cdev)
{
	struct tcan4x5x_priv *tcan4x5x = cdev->device_data;

	tcan4x5x->device_wake_gpio = devm_gpiod_get(cdev->dev, "device-wake",
						    GPIOD_OUT_HIGH);
	if (IS_ERR(tcan4x5x->device_wake_gpio)) {
		dev_err(cdev->dev, "device-wake gpio not defined\n");
		return -EINVAL;
	}

	tcan4x5x->reset_gpio = devm_gpiod_get_optional(cdev->dev, "reset",
						       GPIOD_OUT_LOW);
	if (IS_ERR(tcan4x5x->reset_gpio))
		tcan4x5x->reset_gpio = NULL;

	tcan4x5x->device_state_gpio = devm_gpiod_get_optional(cdev->dev,
							      "device-state",
							      GPIOD_IN);
	if (IS_ERR(tcan4x5x->device_state_gpio))
		tcan4x5x->device_state_gpio = NULL;

	tcan4x5x->power = devm_regulator_get_optional(cdev->dev,
						      "vsup");
	if (PTR_ERR(tcan4x5x->power) == -EPROBE_DEFER)
		return -EPROBE_DEFER;

	return 0;
}