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
struct cap11xx_priv {int /*<<< orphan*/  regmap; scalar_t__ num_leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP11XX_REG_MAIN_CONTROL ; 
 int /*<<< orphan*/  CAP11XX_REG_MAIN_CONTROL_DLSEEP ; 
 int /*<<< orphan*/  CONFIG_LEDS_CLASS ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cap11xx_set_sleep(struct cap11xx_priv *priv, bool sleep)
{
	/*
	 * DLSEEP mode will turn off all LEDS, prevent this
	 */
	if (IS_ENABLED(CONFIG_LEDS_CLASS) && priv->num_leds)
		return 0;

	return regmap_update_bits(priv->regmap, CAP11XX_REG_MAIN_CONTROL,
				  CAP11XX_REG_MAIN_CONTROL_DLSEEP,
				  sleep ? CAP11XX_REG_MAIN_CONTROL_DLSEEP : 0);
}