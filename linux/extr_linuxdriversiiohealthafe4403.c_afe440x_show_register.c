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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct afe440x_attr {size_t field; unsigned int table_size; TYPE_1__* val_table; } ;
struct afe4403_data {int /*<<< orphan*/ * fields; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int integer; int fract; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IIO_VAL_INT_PLUS_MICRO ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 int iio_format_value (char*,int /*<<< orphan*/ ,int,int*) ; 
 struct afe4403_data* iio_priv (struct iio_dev*) ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 
 struct afe440x_attr* to_afe440x_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t afe440x_show_register(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct afe4403_data *afe = iio_priv(indio_dev);
	struct afe440x_attr *afe440x_attr = to_afe440x_attr(attr);
	unsigned int reg_val;
	int vals[2];
	int ret;

	ret = regmap_field_read(afe->fields[afe440x_attr->field], &reg_val);
	if (ret)
		return ret;

	if (reg_val >= afe440x_attr->table_size)
		return -EINVAL;

	vals[0] = afe440x_attr->val_table[reg_val].integer;
	vals[1] = afe440x_attr->val_table[reg_val].fract;

	return iio_format_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, vals);
}