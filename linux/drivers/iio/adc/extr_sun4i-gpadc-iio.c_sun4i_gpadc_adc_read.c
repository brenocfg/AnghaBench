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
struct sun4i_gpadc_iio {int /*<<< orphan*/  fifo_data_irq; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 
 int sun4i_gpadc_read (struct iio_dev*,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun4i_gpadc_adc_read(struct iio_dev *indio_dev, int channel,
				int *val)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);

	return sun4i_gpadc_read(indio_dev, channel, val, info->fifo_data_irq);
}