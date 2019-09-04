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
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;
struct hx711_data {int /*<<< orphan*/  reg_avdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct hx711_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hx711_remove(struct platform_device *pdev)
{
	struct hx711_data *hx711_data;
	struct iio_dev *indio_dev;

	indio_dev = platform_get_drvdata(pdev);
	hx711_data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);

	regulator_disable(hx711_data->reg_avdd);

	return 0;
}