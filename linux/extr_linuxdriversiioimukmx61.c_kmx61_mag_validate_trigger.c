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
struct kmx61_data {struct iio_trigger* mag_dready_trig; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct kmx61_data* kmx61_get_data (struct iio_dev*) ; 

__attribute__((used)) static int kmx61_mag_validate_trigger(struct iio_dev *indio_dev,
				      struct iio_trigger *trig)
{
	struct kmx61_data *data = kmx61_get_data(indio_dev);

	if (data->mag_dready_trig != trig)
		return -EINVAL;

	return 0;
}