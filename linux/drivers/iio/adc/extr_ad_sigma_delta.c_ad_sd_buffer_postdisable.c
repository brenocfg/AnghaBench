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
struct ad_sigma_delta {int irq_dis; int keep_cs_asserted; int bus_locked; TYPE_1__* spi; int /*<<< orphan*/  completion; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_SD_MODE_IDLE ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  ad_sigma_delta_set_mode (struct ad_sigma_delta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 struct ad_sigma_delta* iio_device_get_drvdata (struct iio_dev*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int spi_bus_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad_sd_buffer_postdisable(struct iio_dev *indio_dev)
{
	struct ad_sigma_delta *sigma_delta = iio_device_get_drvdata(indio_dev);

	reinit_completion(&sigma_delta->completion);
	wait_for_completion_timeout(&sigma_delta->completion, HZ);

	if (!sigma_delta->irq_dis) {
		disable_irq_nosync(sigma_delta->spi->irq);
		sigma_delta->irq_dis = true;
	}

	sigma_delta->keep_cs_asserted = false;
	ad_sigma_delta_set_mode(sigma_delta, AD_SD_MODE_IDLE);

	sigma_delta->bus_locked = false;
	return spi_bus_unlock(sigma_delta->spi->master);
}