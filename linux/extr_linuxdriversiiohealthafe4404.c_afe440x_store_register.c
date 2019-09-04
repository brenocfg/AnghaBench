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
struct afe440x_attr {int table_size; size_t field; TYPE_1__* val_table; } ;
struct afe4404_data {int /*<<< orphan*/ * fields; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int integer; int fract; } ;

/* Variables and functions */
 int EINVAL ; 
 struct iio_dev* dev_to_iio_dev (struct device*) ; 
 struct afe4404_data* iio_priv (struct iio_dev*) ; 
 int iio_str_to_fixpoint (char const*,int,int*,int*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 struct afe440x_attr* to_afe440x_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t afe440x_store_register(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct iio_dev *indio_dev = dev_to_iio_dev(dev);
	struct afe4404_data *afe = iio_priv(indio_dev);
	struct afe440x_attr *afe440x_attr = to_afe440x_attr(attr);
	int val, integer, fract, ret;

	ret = iio_str_to_fixpoint(buf, 100000, &integer, &fract);
	if (ret)
		return ret;

	for (val = 0; val < afe440x_attr->table_size; val++)
		if (afe440x_attr->val_table[val].integer == integer &&
		    afe440x_attr->val_table[val].fract == fract)
			break;
	if (val == afe440x_attr->table_size)
		return -EINVAL;

	ret = regmap_field_write(afe->fields[afe440x_attr->field], val);
	if (ret)
		return ret;

	return count;
}