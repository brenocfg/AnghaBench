#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {TYPE_3__* dfsdm; TYPE_1__* dev_data; } ;
struct iio_dev {int dummy; } ;
struct TYPE_6__ {char sign; int realbits; int storagebits; } ;
struct iio_chan_spec {int indexed; size_t channel; TYPE_2__ scan_type; int /*<<< orphan*/  ext_info; void* info_mask_shared_by_all; void* info_mask_separate; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ch_list; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 void* BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DFSDM_AUDIO ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_OVERSAMPLING_RATIO ; 
 int /*<<< orphan*/  IIO_CHAN_INFO_RAW ; 
 int /*<<< orphan*/  IIO_VOLTAGE ; 
 int /*<<< orphan*/  dfsdm_adc_audio_ext_info ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int stm32_dfsdm_chan_configure (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int stm32_dfsdm_channel_parse_of (TYPE_3__*,struct iio_dev*,struct iio_chan_spec*) ; 

__attribute__((used)) static int stm32_dfsdm_adc_chan_init_one(struct iio_dev *indio_dev,
					 struct iio_chan_spec *ch)
{
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	int ret;

	ret = stm32_dfsdm_channel_parse_of(adc->dfsdm, indio_dev, ch);
	if (ret < 0)
		return ret;

	ch->type = IIO_VOLTAGE;
	ch->indexed = 1;

	/*
	 * IIO_CHAN_INFO_RAW: used to compute regular conversion
	 * IIO_CHAN_INFO_OVERSAMPLING_RATIO: used to set oversampling
	 */
	ch->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	ch->info_mask_shared_by_all = BIT(IIO_CHAN_INFO_OVERSAMPLING_RATIO);

	if (adc->dev_data->type == DFSDM_AUDIO) {
		ch->scan_type.sign = 's';
		ch->ext_info = dfsdm_adc_audio_ext_info;
	} else {
		ch->scan_type.sign = 'u';
	}
	ch->scan_type.realbits = 24;
	ch->scan_type.storagebits = 32;

	return stm32_dfsdm_chan_configure(adc->dfsdm,
					  &adc->dfsdm->ch_list[ch->channel]);
}