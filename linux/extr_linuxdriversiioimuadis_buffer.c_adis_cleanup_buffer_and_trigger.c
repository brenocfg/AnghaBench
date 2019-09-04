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
struct iio_dev {int dummy; } ;
struct adis {int /*<<< orphan*/  xfer; int /*<<< orphan*/  buffer; TYPE_1__* spi; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  adis_remove_trigger (struct adis*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void adis_cleanup_buffer_and_trigger(struct adis *adis,
	struct iio_dev *indio_dev)
{
	if (adis->spi->irq)
		adis_remove_trigger(adis);
	kfree(adis->buffer);
	kfree(adis->xfer);
	iio_triggered_buffer_cleanup(indio_dev);
}