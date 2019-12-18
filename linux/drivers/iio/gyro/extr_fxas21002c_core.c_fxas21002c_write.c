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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  prev_mode; int /*<<< orphan*/ * regmap_fields; } ;
typedef  enum fxas21002c_fields { ____Placeholder_fxas21002c_fields } fxas21002c_fields ;

/* Variables and functions */
 int /*<<< orphan*/  FXAS21002C_MODE_READY ; 
 int fxas21002c_mode_get (struct fxas21002c_data*) ; 
 int fxas21002c_mode_set (struct fxas21002c_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fxas21002c_write(struct fxas21002c_data *data,
			    enum fxas21002c_fields field, int bits)
{
	int actual_mode;
	int ret;

	mutex_lock(&data->lock);

	actual_mode = fxas21002c_mode_get(data);
	if (actual_mode < 0) {
		ret = actual_mode;
		goto out_unlock;
	}

	ret = fxas21002c_mode_set(data, FXAS21002C_MODE_READY);
	if (ret < 0)
		goto out_unlock;

	ret = regmap_field_write(data->regmap_fields[field], bits);
	if (ret < 0)
		goto out_unlock;

	ret = fxas21002c_mode_set(data, data->prev_mode);

out_unlock:
	mutex_unlock(&data->lock);

	return ret;
}