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
struct stm32_timers {int /*<<< orphan*/  regmap; int /*<<< orphan*/  max_arr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIM_ARR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32_timers_get_arr_size(struct stm32_timers *ddata)
{
	/*
	 * Only the available bits will be written so when readback
	 * we get the maximum value of auto reload register
	 */
	regmap_write(ddata->regmap, TIM_ARR, ~0L);
	regmap_read(ddata->regmap, TIM_ARR, &ddata->max_arr);
	regmap_write(ddata->regmap, TIM_ARR, 0x0);
}