#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct TYPE_6__ {int realbits; int shift; } ;
struct iio_chan_spec {TYPE_3__ scan_type; int /*<<< orphan*/  address; } ;
struct ad_sigma_delta {int bus_locked; int keep_cs_asserted; int irq_dis; TYPE_2__* spi; TYPE_1__* info; int /*<<< orphan*/  completion; } ;
struct TYPE_5__ {int /*<<< orphan*/  master; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {unsigned int data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_SD_MODE_IDLE ; 
 int /*<<< orphan*/  AD_SD_MODE_SINGLE ; 
 unsigned int AD_SD_REG_DATA ; 
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 int IIO_VAL_INT ; 
 int ad_sd_read_reg (struct ad_sigma_delta*,unsigned int,int /*<<< orphan*/ ,unsigned int*) ; 
 int ad_sigma_delta_postprocess_sample (struct ad_sigma_delta*,unsigned int) ; 
 int /*<<< orphan*/  ad_sigma_delta_set_channel (struct ad_sigma_delta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad_sigma_delta_set_mode (struct ad_sigma_delta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ iio_buffer_enabled (struct iio_dev*) ; 
 struct ad_sigma_delta* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bus_unlock (int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ad_sigma_delta_single_conversion(struct iio_dev *indio_dev,
	const struct iio_chan_spec *chan, int *val)
{
	struct ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	unsigned int sample, raw_sample;
	unsigned int data_reg;
	int ret = 0;

	if (iio_buffer_enabled(indio_dev))
		return -EBUSY;

	mutex_lock(&indio_dev->mlock);
	ad_sigma_delta_set_channel(sigma_delta, chan->address);

	spi_bus_lock(sigma_delta->spi->master);
	sigma_delta->bus_locked = true;
	sigma_delta->keep_cs_asserted = true;
	reinit_completion(&sigma_delta->completion);

	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_SINGLE);

	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);
	ret = wait_for_completion_interruptible_timeout(
			&sigma_delta->completion, HZ);

	if (ret == 0)
		ret = -EIO;
	if (ret < 0)
		goto out;

	if (sigma_delta->info->data_reg != 0)
		data_reg = sigma_delta->info->data_reg;
	else
		data_reg = AD_SD_REG_DATA;

	ret = ad_sd_read_reg(sigma_delta, data_reg,
		DIV_ROUND_UP(chan->scan_type.realbits + chan->scan_type.shift, 8),
		&raw_sample);

out:
	if (!sigma_delta->irq_dis) {
		disable_irq_nosync(sigma_delta->spi->irq);
		sigma_delta->irq_dis = true;
	}

	sigma_delta->keep_cs_asserted = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);
	sigma_delta->bus_locked = false;
	spi_bus_unlock(sigma_delta->spi->master);
	mutex_unlock(&indio_dev->mlock);

	if (ret)
		return ret;

	sample = raw_sample >> chan->scan_type.shift;
	sample &= (1 << chan->scan_type.realbits) - 1;
	*val = sample;

	ret = ad_sigma_delta_postprocess_sample(sigma_delta, raw_sample);
	if (ret)
		return ret;

	return IIO_VAL_INT;
}