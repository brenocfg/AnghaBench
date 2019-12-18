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
typedef  int u32 ;
struct lm90_data {int /*<<< orphan*/  update_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  REMOTE_OFFSET ; 
 struct lm90_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_crit 133 
#define  hwmon_temp_crit_hyst 132 
#define  hwmon_temp_emergency 131 
#define  hwmon_temp_max 130 
#define  hwmon_temp_min 129 
#define  hwmon_temp_offset 128 
 int lm90_set_temp11 (struct lm90_data*,int /*<<< orphan*/ ,long) ; 
 int lm90_set_temp8 (struct lm90_data*,int /*<<< orphan*/ ,long) ; 
 int lm90_set_temphyst (struct lm90_data*,long) ; 
 int /*<<< orphan*/ * lm90_temp_crit_index ; 
 int /*<<< orphan*/ * lm90_temp_emerg_index ; 
 int /*<<< orphan*/ * lm90_temp_max_index ; 
 int /*<<< orphan*/ * lm90_temp_min_index ; 
 int lm90_update_device (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm90_temp_write(struct device *dev, u32 attr, int channel, long val)
{
	struct lm90_data *data = dev_get_drvdata(dev);
	int err;

	mutex_lock(&data->update_lock);

	err = lm90_update_device(dev);
	if (err)
		goto error;

	switch (attr) {
	case hwmon_temp_min:
		if (channel == 0)
			err = lm90_set_temp8(data,
					      lm90_temp_min_index[channel],
					      val);
		else
			err = lm90_set_temp11(data,
					      lm90_temp_min_index[channel],
					      val);
		break;
	case hwmon_temp_max:
		if (channel == 0)
			err = lm90_set_temp8(data,
					     lm90_temp_max_index[channel],
					     val);
		else
			err = lm90_set_temp11(data,
					      lm90_temp_max_index[channel],
					      val);
		break;
	case hwmon_temp_crit:
		err = lm90_set_temp8(data, lm90_temp_crit_index[channel], val);
		break;
	case hwmon_temp_crit_hyst:
		err = lm90_set_temphyst(data, val);
		break;
	case hwmon_temp_emergency:
		err = lm90_set_temp8(data, lm90_temp_emerg_index[channel], val);
		break;
	case hwmon_temp_offset:
		err = lm90_set_temp11(data, REMOTE_OFFSET, val);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}
error:
	mutex_unlock(&data->update_lock);

	return err;
}