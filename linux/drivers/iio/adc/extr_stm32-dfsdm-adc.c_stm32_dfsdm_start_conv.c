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
struct stm32_dfsdm_adc {int /*<<< orphan*/  fl_id; TYPE_1__* dfsdm; } ;
struct regmap {int dummy; } ;
struct iio_trigger {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_CR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR1_CFG_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stm32_dfsdm_channels_configure (struct stm32_dfsdm_adc*,int /*<<< orphan*/ ,struct iio_trigger*) ; 
 int stm32_dfsdm_filter_configure (struct stm32_dfsdm_adc*,int /*<<< orphan*/ ,struct iio_trigger*) ; 
 int stm32_dfsdm_start_channel (struct stm32_dfsdm_adc*) ; 
 int stm32_dfsdm_start_filter (struct stm32_dfsdm_adc*,int /*<<< orphan*/ ,struct iio_trigger*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_channel (struct stm32_dfsdm_adc*) ; 

__attribute__((used)) static int stm32_dfsdm_start_conv(struct stm32_dfsdm_adc *adc,
				  struct iio_trigger *trig)
{
	struct regmap *regmap = adc->dfsdm->regmap;
	int ret;

	ret = stm32_dfsdm_channels_configure(adc, adc->fl_id, trig);
	if (ret < 0)
		return ret;

	ret = stm32_dfsdm_start_channel(adc);
	if (ret < 0)
		return ret;

	ret = stm32_dfsdm_filter_configure(adc, adc->fl_id, trig);
	if (ret < 0)
		goto stop_channels;

	ret = stm32_dfsdm_start_filter(adc, adc->fl_id, trig);
	if (ret < 0)
		goto filter_unconfigure;

	return 0;

filter_unconfigure:
	regmap_update_bits(regmap, DFSDM_CR1(adc->fl_id),
			   DFSDM_CR1_CFG_MASK, 0);
stop_channels:
	stm32_dfsdm_stop_channel(adc);

	return ret;
}