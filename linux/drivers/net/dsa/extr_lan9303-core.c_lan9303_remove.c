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
struct lan9303 {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  ds; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpiod_unexport (int /*<<< orphan*/ ) ; 
 int lan9303_disable_processing (struct lan9303*) ; 

int lan9303_remove(struct lan9303 *chip)
{
	int rc;

	rc = lan9303_disable_processing(chip);
	if (rc != 0)
		dev_warn(chip->dev, "shutting down failed\n");

	dsa_unregister_switch(chip->ds);

	/* assert reset to the whole device to prevent it from doing anything */
	gpiod_set_value_cansleep(chip->reset_gpio, 1);
	gpiod_unexport(chip->reset_gpio);

	return 0;
}