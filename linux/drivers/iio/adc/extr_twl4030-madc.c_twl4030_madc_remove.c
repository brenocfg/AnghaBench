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
struct twl4030_madc_data {int /*<<< orphan*/  usb3v1; } ;
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct twl4030_madc_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_madc_set_current_generator (struct twl4030_madc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_madc_set_power (struct twl4030_madc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_madc_remove(struct platform_device *pdev)
{
	struct iio_dev *iio_dev = platform_get_drvdata(pdev);
	struct twl4030_madc_data *madc = iio_priv(iio_dev);

	iio_device_unregister(iio_dev);

	twl4030_madc_set_current_generator(madc, 0, 0);
	twl4030_madc_set_power(madc, 0);

	regulator_disable(madc->usb3v1);

	return 0;
}