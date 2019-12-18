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
struct max77650_led {int /*<<< orphan*/  regA; int /*<<< orphan*/  map; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int LED_OFF ; 
 int MAX77650_LED_BR_MASK ; 
 int MAX77650_LED_DISABLE ; 
 int MAX77650_LED_ENABLE ; 
 int MAX77650_LED_EN_MASK ; 
 struct max77650_led* max77650_to_led (struct led_classdev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int max77650_led_brightness_set(struct led_classdev *cdev,
				       enum led_brightness brightness)
{
	struct max77650_led *led = max77650_to_led(cdev);
	int val, mask;

	mask = MAX77650_LED_BR_MASK | MAX77650_LED_EN_MASK;

	if (brightness == LED_OFF)
		val = MAX77650_LED_DISABLE;
	else
		val = MAX77650_LED_ENABLE | brightness;

	return regmap_update_bits(led->map, led->regA, mask, val);
}