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
struct led_pattern {int delta_t; int brightness; } ;
struct led_classdev {int brightness; } ;
struct TYPE_2__ {scalar_t__ base; int /*<<< orphan*/  lock; struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 int SC27XX_CTRL_SHIFT ; 
 int SC27XX_CURVE_H_MASK ; 
 int SC27XX_CURVE_L_MASK ; 
 int SC27XX_CURVE_SHIFT ; 
 int SC27XX_DUTY_MASK ; 
 int SC27XX_DUTY_SHIFT ; 
 scalar_t__ SC27XX_LEDS_CTRL ; 
 scalar_t__ SC27XX_LEDS_CURVE0 ; 
 scalar_t__ SC27XX_LEDS_CURVE1 ; 
 scalar_t__ SC27XX_LEDS_DUTY ; 
 scalar_t__ SC27XX_LEDS_PATTERN_CNT ; 
 int SC27XX_LEDS_STEP ; 
 int SC27XX_LED_RUN ; 
 int SC27XX_MOD_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (struct regmap*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  sc27xx_led_clamp_align_delta_t (int*) ; 
 scalar_t__ sc27xx_led_get_offset (struct sc27xx_led*) ; 
 struct sc27xx_led* to_sc27xx_led (struct led_classdev*) ; 

__attribute__((used)) static int sc27xx_led_pattern_set(struct led_classdev *ldev,
				  struct led_pattern *pattern,
				  u32 len, int repeat)
{
	struct sc27xx_led *leds = to_sc27xx_led(ldev);
	u32 base = sc27xx_led_get_offset(leds);
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shift = SC27XX_CTRL_SHIFT * leds->line;
	struct regmap *regmap = leds->priv->regmap;
	int err;

	/*
	 * Must contain 4 tuples to configure the rise time, high time, fall
	 * time and low time to enable the breathing mode.
	 */
	if (len != SC27XX_LEDS_PATTERN_CNT)
		return -EINVAL;

	mutex_lock(&leds->priv->lock);

	sc27xx_led_clamp_align_delta_t(&pattern[0].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE0,
				 SC27XX_CURVE_L_MASK,
				 pattern[0].delta_t / SC27XX_LEDS_STEP);
	if (err)
		goto out;

	sc27xx_led_clamp_align_delta_t(&pattern[1].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE1,
				 SC27XX_CURVE_L_MASK,
				 pattern[1].delta_t / SC27XX_LEDS_STEP);
	if (err)
		goto out;

	sc27xx_led_clamp_align_delta_t(&pattern[2].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE0,
				 SC27XX_CURVE_H_MASK,
				 (pattern[2].delta_t / SC27XX_LEDS_STEP) <<
				 SC27XX_CURVE_SHIFT);
	if (err)
		goto out;

	sc27xx_led_clamp_align_delta_t(&pattern[3].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE1,
				 SC27XX_CURVE_H_MASK,
				 (pattern[3].delta_t / SC27XX_LEDS_STEP) <<
				 SC27XX_CURVE_SHIFT);
	if (err)
		goto out;

	err = regmap_update_bits(regmap, base + SC27XX_LEDS_DUTY,
				 SC27XX_DUTY_MASK,
				 (pattern[1].brightness << SC27XX_DUTY_SHIFT) |
				 SC27XX_MOD_MASK);
	if (err)
		goto out;

	/* Enable the LED breathing mode */
	err = regmap_update_bits(regmap, ctrl_base,
				 SC27XX_LED_RUN << ctrl_shift,
				 SC27XX_LED_RUN << ctrl_shift);
	if (!err)
		ldev->brightness = pattern[1].brightness;

out:
	mutex_unlock(&leds->priv->lock);

	return err;
}