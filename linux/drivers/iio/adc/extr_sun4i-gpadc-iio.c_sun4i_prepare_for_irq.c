#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sun4i_gpadc_iio {unsigned int fifo_data_irq; TYPE_2__* data; int /*<<< orphan*/  regmap; int /*<<< orphan*/  completion; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_1__ dev; } ;
struct TYPE_4__ {int tp_mode_en; int tp_adc_select; int (* adc_chan_select ) (int) ;int adc_chan_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_GPADC_CTRL1 ; 
 int /*<<< orphan*/  SUN4I_GPADC_INT_FIFOC ; 
 int SUN4I_GPADC_INT_FIFOC_TP_FIFO_FLUSH ; 
 int SUN4I_GPADC_INT_FIFOC_TP_FIFO_TRIG_LEVEL (int) ; 
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 

__attribute__((used)) static int sun4i_prepare_for_irq(struct iio_dev *indio_dev, int channel,
				 unsigned int irq)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);
	int ret;
	u32 reg;

	pm_runtime_get_sync(indio_dev->dev.parent);

	reinit_completion(&info->completion);

	ret = regmap_write(info->regmap, SUN4I_GPADC_INT_FIFOC,
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_TRIG_LEVEL(1) |
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_FLUSH);
	if (ret)
		return ret;

	ret = regmap_read(info->regmap, SUN4I_GPADC_CTRL1, &reg);
	if (ret)
		return ret;

	if (irq == info->fifo_data_irq) {
		ret = regmap_write(info->regmap, SUN4I_GPADC_CTRL1,
				   info->data->tp_mode_en |
				   info->data->tp_adc_select |
				   info->data->adc_chan_select(channel));
		/*
		 * When the IP changes channel, it needs a bit of time to get
		 * correct values.
		 */
		if ((reg & info->data->adc_chan_mask) !=
			 info->data->adc_chan_select(channel))
			mdelay(10);

	} else {
		/*
		 * The temperature sensor returns valid data only when the ADC
		 * operates in touchscreen mode.
		 */
		ret = regmap_write(info->regmap, SUN4I_GPADC_CTRL1,
				   info->data->tp_mode_en);
	}

	if (ret)
		return ret;

	/*
	 * When the IP changes mode between ADC or touchscreen, it
	 * needs a bit of time to get correct values.
	 */
	if ((reg & info->data->tp_adc_select) != info->data->tp_adc_select)
		mdelay(100);

	return 0;
}