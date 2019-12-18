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
typedef  scalar_t__ u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct gp2ap020a00f_data {int* thresh_val; int /*<<< orphan*/  lock; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GP2AP020A00F_PH_L_REG ; 
 size_t GP2AP020A00F_THRESH_VAL_ID (scalar_t__) ; 
 int IIO_VAL_INT ; 
 scalar_t__ gp2ap020a00f_get_thresh_reg (struct iio_chan_spec const*,int) ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gp2ap020a00f_read_event_val(struct iio_dev *indio_dev,
				       const struct iio_chan_spec *chan,
				       enum iio_event_type type,
				       enum iio_event_direction dir,
				       enum iio_event_info info,
				       int *val, int *val2)
{
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	u8 thresh_reg_l;
	int err = IIO_VAL_INT;

	mutex_lock(&data->lock);

	thresh_reg_l = gp2ap020a00f_get_thresh_reg(chan, dir);

	if (thresh_reg_l > GP2AP020A00F_PH_L_REG) {
		err = -EINVAL;
		goto error_unlock;
	}

	*val = data->thresh_val[GP2AP020A00F_THRESH_VAL_ID(thresh_reg_l)];

error_unlock:
	mutex_unlock(&data->lock);

	return err;
}