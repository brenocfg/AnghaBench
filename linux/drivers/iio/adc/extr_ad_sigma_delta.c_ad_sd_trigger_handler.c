#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; TYPE_2__* channels; } ;
struct ad_sigma_delta {int irq_dis; TYPE_4__* spi; TYPE_3__* info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {unsigned int data_reg; } ;
struct TYPE_5__ {unsigned int realbits; unsigned int shift; } ;
struct TYPE_6__ {TYPE_1__ scan_type; } ;

/* Variables and functions */
 unsigned int AD_SD_REG_DATA ; 
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ad_sd_read_reg_raw (struct ad_sigma_delta*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct ad_sigma_delta* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static irqreturn_t ad_sd_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);
	unsigned int reg_size;
	unsigned int data_reg;
	uint8_t data[16];
	int ret;

	memset(data, 0x00, 16);

	reg_size = indio_dev->channels[0].scan_type.realbits +
			indio_dev->channels[0].scan_type.shift;
	reg_size = DIV_ROUND_UP(reg_size, 8);

	if (sigma_delta->info->data_reg != 0)
		data_reg = sigma_delta->info->data_reg;
	else
		data_reg = AD_SD_REG_DATA;

	switch (reg_size) {
	case 4:
	case 2:
	case 1:
		ret = ad_sd_read_reg_raw(sigma_delta, data_reg, reg_size,
			&data[0]);
		break;
	case 3:
		/* We store 24 bit samples in a 32 bit word. Keep the upper
		 * byte set to zero. */
		ret = ad_sd_read_reg_raw(sigma_delta, data_reg, reg_size,
			&data[1]);
		break;
	}

	iio_push_to_buffers_with_timestamp(indio_dev, data, pf->timestamp);

	iio_trigger_notify_done(indio_dev->trig);
	sigma_delta->irq_dis = false;
	enable_irq(sigma_delta->spi->irq);

	return IRQ_HANDLED;
}