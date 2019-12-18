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
struct stm32_dac {TYPE_1__* common; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  STM32_DAC_DOR1 ; 
 int /*<<< orphan*/  STM32_DAC_DOR2 ; 
 scalar_t__ STM32_DAC_IS_CHAN_1 (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int stm32_dac_get_value(struct stm32_dac *dac, int channel, int *val)
{
	int ret;

	if (STM32_DAC_IS_CHAN_1(channel))
		ret = regmap_read(dac->common->regmap, STM32_DAC_DOR1, val);
	else
		ret = regmap_read(dac->common->regmap, STM32_DAC_DOR2, val);

	return ret ? ret : IIO_VAL_INT;
}