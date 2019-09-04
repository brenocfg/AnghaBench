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
struct lp55xx_led {size_t chan_nr; int /*<<< orphan*/  brightness; struct lp55xx_chip* chip; } ;
struct lp55xx_chip {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  LP5562_REG_B_PWM 131 
#define  LP5562_REG_G_PWM 130 
#define  LP5562_REG_R_PWM 129 
#define  LP5562_REG_W_PWM 128 
 int lp55xx_write (struct lp55xx_chip*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lp5562_led_brightness(struct lp55xx_led *led)
{
	struct lp55xx_chip *chip = led->chip;
	static const u8 addr[] = {
		LP5562_REG_R_PWM,
		LP5562_REG_G_PWM,
		LP5562_REG_B_PWM,
		LP5562_REG_W_PWM,
	};
	int ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_write(chip, addr[led->chan_nr], led->brightness);
	mutex_unlock(&chip->lock);

	return ret;
}