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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct tiadc_device {int channels; int* channel_step; int /*<<< orphan*/  fifo1_lock; int /*<<< orphan*/  mfd_tscadc; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t scan_index; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 unsigned int FIFOREAD_CHNLID_MASK ; 
 unsigned int FIFOREAD_DATA_MASK ; 
 int IDLE_TIMEOUT ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  REG_FIFO1 ; 
 int /*<<< orphan*/  REG_FIFO1CNT ; 
 int /*<<< orphan*/  am335x_tsc_se_adc_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am335x_tsc_se_set_once (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_adc_chan_step_mask (struct tiadc_device*,struct iio_chan_spec const*) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int tiadc_readl (struct tiadc_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int tiadc_read_raw(struct iio_dev *indio_dev,
		struct iio_chan_spec const *chan,
		int *val, int *val2, long mask)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);
	int ret = IIO_VAL_INT;
	int i, map_val;
	unsigned int fifo1count, read, stepid;
	bool found = false;
	u32 step_en;
	unsigned long timeout;

	if (iio_buffer_enabled(indio_dev))
		return -EBUSY;

	step_en = get_adc_chan_step_mask(adc_dev, chan);
	if (!step_en)
		return -EINVAL;

	mutex_lock(&adc_dev->fifo1_lock);
	fifo1count = tiadc_readl(adc_dev, REG_FIFO1CNT);
	while (fifo1count--)
		tiadc_readl(adc_dev, REG_FIFO1);

	am335x_tsc_se_set_once(adc_dev->mfd_tscadc, step_en);

	timeout = jiffies + msecs_to_jiffies
				(IDLE_TIMEOUT * adc_dev->channels);
	/* Wait for Fifo threshold interrupt */
	while (1) {
		fifo1count = tiadc_readl(adc_dev, REG_FIFO1CNT);
		if (fifo1count)
			break;

		if (time_after(jiffies, timeout)) {
			am335x_tsc_se_adc_done(adc_dev->mfd_tscadc);
			ret = -EAGAIN;
			goto err_unlock;
		}
	}
	map_val = adc_dev->channel_step[chan->scan_index];

	/*
	 * We check the complete FIFO. We programmed just one entry but in case
	 * something went wrong we left empty handed (-EAGAIN previously) and
	 * then the value apeared somehow in the FIFO we would have two entries.
	 * Therefore we read every item and keep only the latest version of the
	 * requested channel.
	 */
	for (i = 0; i < fifo1count; i++) {
		read = tiadc_readl(adc_dev, REG_FIFO1);
		stepid = read & FIFOREAD_CHNLID_MASK;
		stepid = stepid >> 0x10;

		if (stepid == map_val) {
			read = read & FIFOREAD_DATA_MASK;
			found = true;
			*val = (u16) read;
		}
	}
	am335x_tsc_se_adc_done(adc_dev->mfd_tscadc);

	if (!found)
		ret =  -EBUSY;

err_unlock:
	mutex_unlock(&adc_dev->fifo1_lock);
	return ret;
}