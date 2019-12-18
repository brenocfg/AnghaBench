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
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __stm32_adc_buffer_predisable (struct iio_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int iio_triggered_buffer_predisable (struct iio_dev*) ; 

__attribute__((used)) static int stm32_adc_buffer_predisable(struct iio_dev *indio_dev)
{
	int ret;

	__stm32_adc_buffer_predisable(indio_dev);

	ret = iio_triggered_buffer_predisable(indio_dev);
	if (ret < 0)
		dev_err(&indio_dev->dev, "predisable failed\n");

	return ret;
}