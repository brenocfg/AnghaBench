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
struct stm32_lptimer {int has_encoder; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_LPTIM_CFGR ; 
 int STM32_LPTIM_ENC ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int stm32_lptimer_detect_encoder(struct stm32_lptimer *ddata)
{
	u32 val;
	int ret;

	/*
	 * Quadrature encoder mode bit can only be written and read back when
	 * Low-Power Timer supports it.
	 */
	ret = regmap_update_bits(ddata->regmap, STM32_LPTIM_CFGR,
				 STM32_LPTIM_ENC, STM32_LPTIM_ENC);
	if (ret)
		return ret;

	ret = regmap_read(ddata->regmap, STM32_LPTIM_CFGR, &val);
	if (ret)
		return ret;

	ret = regmap_update_bits(ddata->regmap, STM32_LPTIM_CFGR,
				 STM32_LPTIM_ENC, 0);
	if (ret)
		return ret;

	ddata->has_encoder = !!(val & STM32_LPTIM_ENC);

	return 0;
}