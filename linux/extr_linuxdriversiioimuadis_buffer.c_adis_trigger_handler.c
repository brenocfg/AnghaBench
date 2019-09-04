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
struct iio_poll_func {int /*<<< orphan*/  timestamp; struct iio_dev* indio_dev; } ;
struct iio_dev {int /*<<< orphan*/  trig; } ;
struct adis {scalar_t__ current_page; int /*<<< orphan*/  buffer; int /*<<< orphan*/  txrx_lock; TYPE_1__* data; TYPE_2__* spi; int /*<<< orphan*/  msg; scalar_t__* tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ has_paging; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS_REG_PAGE_ID ; 
 scalar_t__ ADIS_WRITE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct adis* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_to_buffers_with_timestamp (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_notify_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_write (TYPE_2__*,scalar_t__*,int) ; 

__attribute__((used)) static irqreturn_t adis_trigger_handler(int irq, void *p)
{
	struct iio_poll_func *pf = p;
	struct iio_dev *indio_dev = pf->indio_dev;
	struct adis *adis = iio_device_get_drvdata(indio_dev);
	int ret;

	if (!adis->buffer)
		return -ENOMEM;

	if (adis->data->has_paging) {
		mutex_lock(&adis->txrx_lock);
		if (adis->current_page != 0) {
			adis->tx[0] = ADIS_WRITE_REG(ADIS_REG_PAGE_ID);
			adis->tx[1] = 0;
			spi_write(adis->spi, adis->tx, 2);
		}
	}

	ret = spi_sync(adis->spi, &adis->msg);
	if (ret)
		dev_err(&adis->spi->dev, "Failed to read data: %d", ret);


	if (adis->data->has_paging) {
		adis->current_page = 0;
		mutex_unlock(&adis->txrx_lock);
	}

	iio_push_to_buffers_with_timestamp(indio_dev, adis->buffer,
		pf->timestamp);

	iio_trigger_notify_done(indio_dev->trig);

	return IRQ_HANDLED;
}