#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {int* buffer; int nconv; TYPE_1__* dfsdm; int /*<<< orphan*/  fl_id; int /*<<< orphan*/  completion; int /*<<< orphan*/  smask; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  scan_index; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFSDM_CR2_REOCIE (int) ; 
 int /*<<< orphan*/  DFSDM_CR2_REOCIE_MASK ; 
 int /*<<< orphan*/  DFSDM_TIMEOUT ; 
 int ETIMEDOUT ; 
 int IIO_VAL_INT ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stm32_dfsdm_start_conv (struct stm32_dfsdm_adc*,int /*<<< orphan*/ *) ; 
 int stm32_dfsdm_start_dfsdm (TYPE_1__*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_conv (struct stm32_dfsdm_adc*) ; 
 int /*<<< orphan*/  stm32_dfsdm_stop_dfsdm (TYPE_1__*) ; 
 long wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_dfsdm_single_conv(struct iio_dev *indio_dev,
				   const struct iio_chan_spec *chan, int *res)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	long timeout;
	int ret;

	reinit_completion(&adc->completion);

	adc->buffer = res;

	ret = stm32_dfsdm_start_dfsdm(adc->dfsdm);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
				 DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(1));
	if (ret < 0)
		goto stop_dfsdm;

	adc->nconv = 1;
	adc->smask = BIT(chan->scan_index);
	ret = stm32_dfsdm_start_conv(adc, NULL);
	if (ret < 0) {
		regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
				   DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(0));
		goto stop_dfsdm;
	}

	timeout = wait_for_completion_interruptible_timeout(&adc->completion,
							    DFSDM_TIMEOUT);

	/* Mask IRQ for regular conversion achievement*/
	regmap_update_bits(adc->dfsdm->regmap, DFSDM_CR2(adc->fl_id),
			   DFSDM_CR2_REOCIE_MASK, DFSDM_CR2_REOCIE(0));

	if (timeout == 0)
		ret = -ETIMEDOUT;
	else if (timeout < 0)
		ret = timeout;
	else
		ret = IIO_VAL_INT;

	stm32_dfsdm_stop_conv(adc);

stop_dfsdm:
	stm32_dfsdm_stop_dfsdm(adc->dfsdm);

	return ret;
}