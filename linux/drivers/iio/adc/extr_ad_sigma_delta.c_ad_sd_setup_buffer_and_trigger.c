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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_sd_buffer_setup_ops ; 
 int ad_sd_probe_trigger (struct iio_dev*) ; 
 int /*<<< orphan*/  ad_sd_trigger_handler ; 
 int /*<<< orphan*/  iio_pollfunc_store_time ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 int iio_triggered_buffer_setup (struct iio_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ad_sd_setup_buffer_and_trigger(struct iio_dev *indio_dev)
{
	int ret;

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_time,
			&ad_sd_trigger_handler, &ad_sd_buffer_setup_ops);
	if (ret)
		return ret;

	ret = ad_sd_probe_trigger(indio_dev);
	if (ret) {
		iio_triggered_buffer_cleanup(indio_dev);
		return ret;
	}

	return 0;
}