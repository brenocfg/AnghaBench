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
typedef  int u8 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct gp2ap020a00f_data {int* thresh_val; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_RISING_EV ; 
#define  GP2AP020A00F_PH_L_REG 131 
#define  GP2AP020A00F_PL_L_REG 130 
 int GP2AP020A00F_THRESH_PH ; 
 int GP2AP020A00F_THRESH_VAL_ID (int) ; 
#define  GP2AP020A00F_TH_L_REG 129 
#define  GP2AP020A00F_TL_L_REG 128 
 int gp2ap020a00f_get_thresh_reg (struct iio_chan_spec const*,int) ; 
 int gp2ap020a00f_write_event_threshold (struct gp2ap020a00f_data*,int,int) ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gp2ap020a00f_write_event_val(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_direction dir,
					enum iio_event_info info,
					int val, int val2)
{
	struct gp2ap020a00f_data *data = iio_priv(indio_dev);
	bool event_en = false;
	u8 thresh_val_id;
	u8 thresh_reg_l;
	int err = 0;

	mutex_lock(&data->lock);

	thresh_reg_l = gp2ap020a00f_get_thresh_reg(chan, dir);
	thresh_val_id = GP2AP020A00F_THRESH_VAL_ID(thresh_reg_l);

	if (thresh_val_id > GP2AP020A00F_THRESH_PH) {
		err = -EINVAL;
		goto error_unlock;
	}

	switch (thresh_reg_l) {
	case GP2AP020A00F_TH_L_REG:
		event_en = test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV,
							&data->flags);
		break;
	case GP2AP020A00F_TL_L_REG:
		event_en = test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV,
							&data->flags);
		break;
	case GP2AP020A00F_PH_L_REG:
		if (val == 0) {
			err = -EINVAL;
			goto error_unlock;
		}
		event_en = test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV,
							&data->flags);
		break;
	case GP2AP020A00F_PL_L_REG:
		if (val == 0) {
			err = -EINVAL;
			goto error_unlock;
		}
		event_en = test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV,
							&data->flags);
		break;
	}

	data->thresh_val[thresh_val_id] = val;
	err =  gp2ap020a00f_write_event_threshold(data, thresh_val_id,
							event_en);
error_unlock:
	mutex_unlock(&data->lock);

	return err;
}