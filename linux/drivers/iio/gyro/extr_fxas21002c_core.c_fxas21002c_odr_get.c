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
struct fxas21002c_data {int /*<<< orphan*/  lock; int /*<<< orphan*/ * regmap_fields; } ;

/* Variables and functions */
 size_t F_DR ; 
 int IIO_VAL_INT ; 
 int fxas21002c_odr_hz_from_value (struct fxas21002c_data*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int fxas21002c_odr_get(struct fxas21002c_data *data, int *odr)
{
	unsigned int odr_bits;
	int ret;

	mutex_lock(&data->lock);
	ret = regmap_field_read(data->regmap_fields[F_DR], &odr_bits);
	if (ret < 0)
		goto data_unlock;

	*odr = fxas21002c_odr_hz_from_value(data, odr_bits);

	ret = IIO_VAL_INT;

data_unlock:
	mutex_unlock(&data->lock);

	return ret;
}