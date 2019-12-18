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
struct iio_chan_spec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_lock; } ;
struct cros_ec_lid_angle_state {TYPE_1__ core; } ;
typedef  int s16 ;

/* Variables and functions */
 int IIO_VAL_INT ; 
 int cros_ec_sensors_read_lid_angle (struct iio_dev*,int,int*) ; 
 struct cros_ec_lid_angle_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_lid_angle_read(struct iio_dev *indio_dev,
				    struct iio_chan_spec const *chan,
				    int *val, int *val2, long mask)
{
	struct cros_ec_lid_angle_state *st = iio_priv(indio_dev);
	s16 data;
	int ret;

	mutex_lock(&st->core.cmd_lock);
	ret = cros_ec_sensors_read_lid_angle(indio_dev, 1, &data);
	if (ret == 0) {
		*val = data;
		ret = IIO_VAL_INT;
	}
	mutex_unlock(&st->core.cmd_lock);
	return ret;
}