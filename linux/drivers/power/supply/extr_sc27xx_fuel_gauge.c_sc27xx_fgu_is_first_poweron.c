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
 int SC27XX_FGU_DEFAULT_CAP ; 
 int SC27XX_FGU_FIRST_POWERTON ; 
 int SC27XX_FGU_MODE_AREA_MASK ; 
 int SC27XX_FGU_MODE_AREA_SHIFT ; 
 scalar_t__ SC27XX_FGU_USER_AREA_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static bool sc27xx_fgu_is_first_poweron(struct sc27xx_fgu_data *data)
{
	int ret, status, cap, mode;

	ret = regmap_read(data->regmap,
			  data->base + SC27XX_FGU_USER_AREA_STATUS, &status);
	if (ret)
		return false;

	/*
	 * We use low 4 bits to save the last battery capacity and high 12 bits
	 * to save the system boot mode.
	 */
	mode = (status & SC27XX_FGU_MODE_AREA_MASK) >> SC27XX_FGU_MODE_AREA_SHIFT;
	cap = status & SC27XX_FGU_CAP_AREA_MASK;

	/*
	 * When FGU has been powered down, the user area registers became
	 * default value (0xffff), which can be used to valid if the system is
	 * first power on or not.
	 */
	if (mode == SC27XX_FGU_FIRST_POWERTON || cap == SC27XX_FGU_DEFAULT_CAP)
		return true;

	return false;
}