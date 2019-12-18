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
 int iio_triggered_buffer_postenable (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_predisable (struct iio_dev*) ; 
 int st_sensors_set_enable (struct iio_dev*,int) ; 

__attribute__((used)) static int st_magn_buffer_postenable(struct iio_dev *indio_dev)
{
	int err;

	err = iio_triggered_buffer_postenable(indio_dev);
	if (err < 0)
		return err;

	err = st_sensors_set_enable(indio_dev, true);
	if (err < 0)
		goto st_magn_buffer_predisable;

	return 0;

st_magn_buffer_predisable:
	iio_triggered_buffer_predisable(indio_dev);
	return err;
}