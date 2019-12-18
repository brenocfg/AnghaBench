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
typedef  int /*<<< orphan*/  u8 ;
struct tlc591xx_priv {int /*<<< orphan*/  regmap; } ;
struct tlc591xx_led {int /*<<< orphan*/  led_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLC591XX_REG_PWM (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tlc591xx_set_pwm(struct tlc591xx_priv *priv, struct tlc591xx_led *led,
		 u8 brightness)
{
	u8 pwm = TLC591XX_REG_PWM(led->led_no);

	return regmap_write(priv->regmap, pwm, brightness);
}