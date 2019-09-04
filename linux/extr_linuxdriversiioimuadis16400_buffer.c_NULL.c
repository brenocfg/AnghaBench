#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct adis {void* buffer; TYPE_2__* spi; int /*<<< orphan*/  msg; } ;
struct adis16400_state {TYPE_1__* variant; struct adis adis; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {scalar_t__ max_speed_hz; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int ADIS16400_BURST_DIAG_STAT ; 
 int ADIS16400_NO_BURST ; 
 scalar_t__ ADIS16400_SPI_BURST ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct adis16400_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_setup (TYPE_2__*) ; 
 int spi_sync (TYPE_2__*,int /*<<< orphan*/ *) ; 

irqreturn_t adis16400_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct adis16400_state *st = iio_priv(indio_dev);
	struct adis *adis = &st->adis;
	u32 old_speed_hz = st->adis.spi->max_speed_hz;
	void *buffer;
	int ret;

	if (!adis->buffer)
		return -ENOMEM;

	if (!(st->variant->flags & ADIS16400_NO_BURST) &&
		st->adis.spi->max_speed_hz > ADIS16400_SPI_BURST) {
		st->adis.spi->max_speed_hz = ADIS16400_SPI_BURST;
		spi_setup(st->adis.spi);
	}

	ret = spi_sync(adis->spi, &adis->msg);
	if (ret)
		dev_err(&adis->spi->dev, "Failed to read data: %d\n", ret);

	if (!(st->variant->flags & ADIS16400_NO_BURST)) {
		st->adis.spi->max_speed_hz = old_speed_hz;
		spi_setup(st->adis.spi);
	}

	if (st->variant->flags & ADIS16400_BURST_DIAG_STAT)
		buffer = adis->buffer + sizeof(u16);
	else
		buffer = adis->buffer;

	iio_push_to_buffers_with_timestamp(indio_dev, buffer,
		pf->timestamp);

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}