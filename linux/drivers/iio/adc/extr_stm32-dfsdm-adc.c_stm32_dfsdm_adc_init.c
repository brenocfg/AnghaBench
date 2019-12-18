#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stm32_dfsdm_adc {int /*<<< orphan*/  completion; int /*<<< orphan*/  hwc; TYPE_1__* dfsdm; int /*<<< orphan*/  oversamp; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/  modes; TYPE_2__ dev; struct iio_chan_spec* channels; } ;
struct iio_chan_spec {int scan_index; } ;
struct TYPE_6__ {int num_chs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFSDM_DEFAULT_OVERSAMPLING ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INDIO_HARDWARE_TRIGGERED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_iio_hw_consumer_alloc (TYPE_2__*) ; 
 struct iio_chan_spec* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 struct stm32_dfsdm_adc* iio_priv (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int of_property_count_u32_elems (int /*<<< orphan*/ ,char*) ; 
 int stm32_dfsdm_adc_chan_init_one (struct iio_dev*,struct iio_chan_spec*) ; 
 int /*<<< orphan*/  stm32_dfsdm_adc_trigger_handler ; 
 int /*<<< orphan*/  stm32_dfsdm_buffer_setup_ops ; 
 int stm32_dfsdm_compute_all_osrs (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_dfsdm_dma_release (struct iio_dev*) ; 
 scalar_t__ stm32_dfsdm_dma_request (struct iio_dev*) ; 

__attribute__((used)) static int stm32_dfsdm_adc_init(struct iio_dev *indio_dev)
{
	struct iio_chan_spec *ch;
	struct stm32_dfsdm_adc *adc = iio_priv(indio_dev);
	int num_ch;
	int ret, chan_idx;

	adc->oversamp = DFSDM_DEFAULT_OVERSAMPLING;
	ret = stm32_dfsdm_compute_all_osrs(indio_dev, adc->oversamp);
	if (ret < 0)
		return ret;

	num_ch = of_property_count_u32_elems(indio_dev->dev.of_node,
					     "st,adc-channels");
	if (num_ch < 0 || num_ch > adc->dfsdm->num_chs) {
		dev_err(&indio_dev->dev, "Bad st,adc-channels\n");
		return num_ch < 0 ? num_ch : -EINVAL;
	}

	/* Bind to SD modulator IIO device */
	adc->hwc = devm_iio_hw_consumer_alloc(&indio_dev->dev);
	if (IS_ERR(adc->hwc))
		return -EPROBE_DEFER;

	ch = devm_kcalloc(&indio_dev->dev, num_ch, sizeof(*ch),
			  GFP_KERNEL);
	if (!ch)
		return -ENOMEM;

	for (chan_idx = 0; chan_idx < num_ch; chan_idx++) {
		ch[chan_idx].scan_index = chan_idx;
		ret = stm32_dfsdm_adc_chan_init_one(indio_dev, &ch[chan_idx]);
		if (ret < 0) {
			dev_err(&indio_dev->dev, "Channels init failed\n");
			return ret;
		}
	}

	indio_dev->num_channels = num_ch;
	indio_dev->channels = ch;

	init_completion(&adc->completion);

	/* Optionally request DMA */
	if (stm32_dfsdm_dma_request(indio_dev)) {
		dev_dbg(&indio_dev->dev, "No DMA support\n");
		return 0;
	}

	ret = iio_triggered_buffer_setup(indio_dev,
					 &iio_pollfunc_store_time,
					 &stm32_dfsdm_adc_trigger_handler,
					 &stm32_dfsdm_buffer_setup_ops);
	if (ret) {
		stm32_dfsdm_dma_release(indio_dev);
		dev_err(&indio_dev->dev, "buffer setup failed\n");
		return ret;
	}

	/* lptimer/timer hardware triggers */
	indio_dev->modes |= INDIO_HARDWARE_TRIGGERED;

	return 0;
}