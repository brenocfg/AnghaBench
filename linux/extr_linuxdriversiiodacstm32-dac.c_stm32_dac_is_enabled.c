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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_dac {TYPE_1__* common; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STM32_DAC_CR ; 
 int /*<<< orphan*/  STM32_DAC_CR_EN1 ; 
 int /*<<< orphan*/  STM32_DAC_CR_EN2 ; 
 scalar_t__ STM32_DAC_IS_CHAN_1 (int) ; 
 struct stm32_dac* iio_priv (struct iio_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stm32_dac_is_enabled(struct iio_dev *indio_dev, int channel)
{
	struct stm32_dac *dac = iio_priv(indio_dev);
	u32 en, val;
	int ret;

	ret = regmap_read(dac->common->regmap, STM32_DAC_CR, &val);
	if (ret < 0)
		return ret;
	if (STM32_DAC_IS_CHAN_1(channel))
		en = FIELD_GET(STM32_DAC_CR_EN1, val);
	else
		en = FIELD_GET(STM32_DAC_CR_EN2, val);

	return !!en;
}