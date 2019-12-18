#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct sc27xx_led {int line; TYPE_1__* priv; } ;
struct regmap {int dummy; } ;
struct led_classdev {int /*<<< orphan*/  brightness; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ base; struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_OFF ; 
 int SC27XX_CTRL_SHIFT ; 
 scalar_t__ SC27XX_LEDS_CTRL ; 
 scalar_t__ SC27XX_LEDS_CURVE0 ; 
 scalar_t__ SC27XX_LEDS_CURVE1 ; 
 int SC27XX_LED_RUN ; 
 int SC27XX_LED_TYPE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (struct regmap*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sc27xx_led_get_offset (struct sc27xx_led*) ; 
 struct sc27xx_led* to_sc27xx_led (struct led_classdev*) ; 

__attribute__((used)) static int sc27xx_led_pattern_clear(struct led_classdev *ldev)
{
	struct sc27xx_led *leds = to_sc27xx_led(ldev);
	struct regmap *regmap = leds->priv->regmap;
	u32 base = sc27xx_led_get_offset(leds);
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shift = SC27XX_CTRL_SHIFT * leds->line;
	int err;

	mutex_lock(&leds->priv->lock);

	/* Reset the rise, high, fall and low time to zero. */
	regmap_write(regmap, base + SC27XX_LEDS_CURVE0, 0);
	regmap_write(regmap, base + SC27XX_LEDS_CURVE1, 0);

	err = regmap_update_bits(regmap, ctrl_base,
			(SC27XX_LED_RUN | SC27XX_LED_TYPE) << ctrl_shift, 0);

	ldev->brightness = LED_OFF;

	mutex_unlock(&leds->priv->lock);

	return err;
}