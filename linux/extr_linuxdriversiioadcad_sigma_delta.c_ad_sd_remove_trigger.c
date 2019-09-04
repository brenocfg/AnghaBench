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
struct ad_sigma_delta {int /*<<< orphan*/  trig; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ad_sigma_delta*) ; 
 struct ad_sigma_delta* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_sd_remove_trigger(struct iio_dev *indio_dev)
{
	struct ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);

	iio_trigger_unregister(sigma_delta->trig);
	free_irq(sigma_delta->spi->irq, sigma_delta);
	iio_trigger_free(sigma_delta->trig);
}