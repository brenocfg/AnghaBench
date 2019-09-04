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
struct lan9303 {scalar_t__ reset_duration; int /*<<< orphan*/  reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

__attribute__((used)) static void lan9303_handle_reset(struct lan9303 *chip)
{
	if (!chip->reset_gpio)
		return;

	if (chip->reset_duration != 0)
		msleep(chip->reset_duration);

	/* release (deassert) reset and activate the device */
	gpiod_set_value_cansleep(chip->reset_gpio, 0);
}