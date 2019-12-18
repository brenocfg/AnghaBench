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
struct tlc591xx_priv {int dummy; } ;
struct tlc591xx_led {struct tlc591xx_priv* priv; } ;
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  LEDOUT_DIM ; 
 int /*<<< orphan*/  LEDOUT_OFF ; 
 int /*<<< orphan*/  LEDOUT_ON ; 
#define  LED_FULL 128 
 struct tlc591xx_led* ldev_to_led (struct led_classdev*) ; 
 int tlc591xx_set_ledout (struct tlc591xx_priv*,struct tlc591xx_led*,int /*<<< orphan*/ ) ; 
 int tlc591xx_set_pwm (struct tlc591xx_priv*,struct tlc591xx_led*,int) ; 

__attribute__((used)) static int
tlc591xx_brightness_set(struct led_classdev *led_cdev,
			enum led_brightness brightness)
{
	struct tlc591xx_led *led = ldev_to_led(led_cdev);
	struct tlc591xx_priv *priv = led->priv;
	int err;

	switch (brightness) {
	case 0:
		err = tlc591xx_set_ledout(priv, led, LEDOUT_OFF);
		break;
	case LED_FULL:
		err = tlc591xx_set_ledout(priv, led, LEDOUT_ON);
		break;
	default:
		err = tlc591xx_set_ledout(priv, led, LEDOUT_DIM);
		if (!err)
			err = tlc591xx_set_pwm(priv, led, brightness);
	}

	return err;
}