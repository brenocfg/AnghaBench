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
typedef  scalar_t__ u32 ;
struct stm32_dac {TYPE_1__* common; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ hfsel; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  STM32_DAC_CR ; 
 scalar_t__ STM32_DAC_CR_EN1 ; 
 scalar_t__ STM32_DAC_CR_EN2 ; 
 scalar_t__ STM32_DAC_IS_CHAN_1 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 struct stm32_dac* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_dac_set_enable_state(struct iio_dev *indio_dev, int ch,
				      bool enable)
{
	struct stm32_dac *dac = iio_priv(indio_dev);
	u32 msk = STM32_DAC_IS_CHAN_1(ch) ? STM32_DAC_CR_EN1 : STM32_DAC_CR_EN2;
	u32 en = enable ? msk : 0;
	int ret;

	ret = regmap_update_bits(dac->common->regmap, STM32_DAC_CR, msk, en);
	if (ret < 0) {
		dev_err(&indio_dev->dev, "%s failed\n", en ?
			"Enable" : "Disable");
		return ret;
	}

	/*
	 * When HFSEL is set, it is not allowed to write the DHRx register
	 * during 8 clock cycles after the ENx bit is set. It is not allowed
	 * to make software/hardware trigger during this period either.
	 */
	if (en && dac->common->hfsel)
		udelay(1);

	return 0;
}