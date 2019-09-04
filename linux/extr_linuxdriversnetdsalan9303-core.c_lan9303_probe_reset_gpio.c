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
struct lan9303 {int reset_duration; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int lan9303_probe_reset_gpio(struct lan9303 *chip,
				     struct device_node *np)
{
	chip->reset_gpio = devm_gpiod_get_optional(chip->dev, "reset",
						   GPIOD_OUT_LOW);
	if (IS_ERR(chip->reset_gpio))
		return PTR_ERR(chip->reset_gpio);

	if (!chip->reset_gpio) {
		dev_dbg(chip->dev, "No reset GPIO defined\n");
		return 0;
	}

	chip->reset_duration = 200;

	if (np) {
		of_property_read_u32(np, "reset-duration",
				     &chip->reset_duration);
	} else {
		dev_dbg(chip->dev, "reset duration defaults to 200 ms\n");
	}

	/* A sane reset duration should not be longer than 1s */
	if (chip->reset_duration > 1000)
		chip->reset_duration = 1000;

	return 0;
}