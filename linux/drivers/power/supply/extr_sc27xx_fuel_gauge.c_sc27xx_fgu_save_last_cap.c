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
struct sc27xx_fgu_data {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int SC27XX_FGU_CAP_AREA_MASK ; 
 scalar_t__ SC27XX_FGU_USER_AREA_CLEAR ; 
 scalar_t__ SC27XX_FGU_USER_AREA_SET ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sc27xx_fgu_save_last_cap(struct sc27xx_fgu_data *data, int cap)
{
	int ret;

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_CLEAR,
				 SC27XX_FGU_CAP_AREA_MASK,
				 SC27XX_FGU_CAP_AREA_MASK);
	if (ret)
		return ret;

	/*
	 * Since the user area registers are put on power always-on region,
	 * then these registers changing time will be a little long. Thus
	 * here we should delay 200us to wait until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	ret = regmap_update_bits(data->regmap,
				 data->base + SC27XX_FGU_USER_AREA_SET,
				 SC27XX_FGU_CAP_AREA_MASK, cap);
	if (ret)
		return ret;

	/*
	 * Since the user area registers are put on power always-on region,
	 * then these registers changing time will be a little long. Thus
	 * here we should delay 200us to wait until values are updated
	 * successfully according to the datasheet.
	 */
	udelay(200);

	/*
	 * According to the datasheet, we should set the USER_AREA_CLEAR to 0 to
	 * make the user area data available, otherwise we can not save the user
	 * area data.
	 */
	return regmap_update_bits(data->regmap,
				  data->base + SC27XX_FGU_USER_AREA_CLEAR,
				  SC27XX_FGU_CAP_AREA_MASK, 0);
}