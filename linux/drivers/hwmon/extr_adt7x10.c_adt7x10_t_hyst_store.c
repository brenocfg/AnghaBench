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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7x10_data {void* hyst; int /*<<< orphan*/ * temp; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ADT7X10_REG_TO_TEMP (struct adt7x10_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADT7X10_TEMP_MAX ; 
 int /*<<< orphan*/  ADT7X10_TEMP_MIN ; 
 int /*<<< orphan*/  ADT7X10_T_HYST ; 
 int /*<<< orphan*/  ADT7X10_T_HYST_MASK ; 
 long DIV_ROUND_CLOSEST (int,int) ; 
 int adt7x10_write_byte (struct device*,int /*<<< orphan*/ ,void*) ; 
 void* clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adt7x10_data* dev_get_drvdata (struct device*) ; 
 int kstrtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t adt7x10_t_hyst_store(struct device *dev,
				    struct device_attribute *da,
				    const char *buf, size_t count)
{
	struct adt7x10_data *data = dev_get_drvdata(dev);
	int limit, ret;
	long hyst;

	ret = kstrtol(buf, 10, &hyst);
	if (ret)
		return ret;
	/* convert absolute hysteresis value to a 4 bit delta value */
	limit = ADT7X10_REG_TO_TEMP(data, data->temp[1]);
	hyst = clamp_val(hyst, ADT7X10_TEMP_MIN, ADT7X10_TEMP_MAX);
	data->hyst = clamp_val(DIV_ROUND_CLOSEST(limit - hyst, 1000),
				   0, ADT7X10_T_HYST_MASK);
	ret = adt7x10_write_byte(dev, ADT7X10_T_HYST, data->hyst);
	if (ret)
		return ret;

	return count;
}