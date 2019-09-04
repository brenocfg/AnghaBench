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
struct sun4i_gpadc_iio {int /*<<< orphan*/  indio_dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  sun4i_gpadc_temp_offset (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ sun4i_gpadc_temp_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sun4i_gpadc_temp_scale (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sun4i_gpadc_get_temp(void *data, int *temp)
{
	struct sun4i_gpadc_iio *info = data;
	int val, scale, offset;

	if (sun4i_gpadc_temp_read(info->indio_dev, &val))
		return -ETIMEDOUT;

	sun4i_gpadc_temp_scale(info->indio_dev, &scale);
	sun4i_gpadc_temp_offset(info->indio_dev, &offset);

	*temp = (val + offset) * scale;

	return 0;
}