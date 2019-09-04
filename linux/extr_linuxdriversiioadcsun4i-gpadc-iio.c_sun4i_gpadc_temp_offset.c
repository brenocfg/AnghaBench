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
struct sun4i_gpadc_iio {TYPE_1__* data; } ;
struct iio_dev {int dummy; } ;
struct TYPE_2__ {int temp_offset; } ;

/* Variables and functions */
 struct sun4i_gpadc_iio* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int sun4i_gpadc_temp_offset(struct iio_dev *indio_dev, int *val)
{
	struct sun4i_gpadc_iio *info = iio_priv(indio_dev);

	*val = info->data->temp_offset;

	return 0;
}