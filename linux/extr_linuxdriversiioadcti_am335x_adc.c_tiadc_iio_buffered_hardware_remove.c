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
struct tiadc_device {TYPE_1__* mfd_tscadc; } ;
struct iio_dev {int /*<<< orphan*/  buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_kfifo_free (int /*<<< orphan*/ ) ; 
 struct tiadc_device* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static void tiadc_iio_buffered_hardware_remove(struct iio_dev *indio_dev)
{
	struct tiadc_device *adc_dev = iio_priv(indio_dev);

	free_irq(adc_dev->mfd_tscadc->irq, indio_dev);
	iio_kfifo_free(indio_dev->buffer);
}