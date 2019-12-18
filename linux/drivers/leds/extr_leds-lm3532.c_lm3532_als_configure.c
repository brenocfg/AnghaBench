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
typedef  int u32 ;
struct lm3532_led {int dummy; } ;
struct lm3532_data {int /*<<< orphan*/  regmap; struct lm3532_als_data* als_data; } ;
struct lm3532_als_data {int als_vmin; int als_vmax; int* zones_lo; int* zones_hi; int config; int als_avrg_time; int als_input_mode; } ;

/* Variables and functions */
 int LED_FULL ; 
 int LM3532_ALS_CONFIG ; 
 int LM3532_ALS_OFFSET_mV ; 
 int LM3532_ALS_SEL_SHIFT ; 
 int LM3532_ALS_ZB_MAX ; 
 int LM3532_ENABLE_ALS ; 
 int LM3532_REG_ZN_0_HI ; 
 int regmap_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm3532_als_configure(struct lm3532_data *priv,
				struct lm3532_led *led)
{
	struct lm3532_als_data *als = priv->als_data;
	u32 als_vmin, als_vmax, als_vstep;
	int zone_reg = LM3532_REG_ZN_0_HI;
	int ret;
	int i;

	als_vmin = als->als_vmin;
	als_vmax = als->als_vmax;

	als_vstep = (als_vmax - als_vmin) / ((LM3532_ALS_ZB_MAX + 1) * 2);

	for (i = 0; i < LM3532_ALS_ZB_MAX; i++) {
		als->zones_lo[i] = ((als_vmin + als_vstep + (i * als_vstep)) *
				LED_FULL) / 1000;
		als->zones_hi[i] = ((als_vmin + LM3532_ALS_OFFSET_mV +
				als_vstep + (i * als_vstep)) * LED_FULL) / 1000;

		zone_reg = LM3532_REG_ZN_0_HI + i * 2;
		ret = regmap_write(priv->regmap, zone_reg, als->zones_lo[i]);
		if (ret)
			return ret;

		zone_reg += 1;
		ret = regmap_write(priv->regmap, zone_reg, als->zones_hi[i]);
		if (ret)
			return ret;
	}

	als->config = (als->als_avrg_time | (LM3532_ENABLE_ALS) |
		(als->als_input_mode << LM3532_ALS_SEL_SHIFT));

	return regmap_write(priv->regmap, LM3532_ALS_CONFIG, als->config);
}