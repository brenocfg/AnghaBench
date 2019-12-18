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
struct sht15_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct sht15_data* dev_get_drvdata (struct device*) ; 
 int sht15_calc_temp (struct sht15_data*) ; 
 int sht15_update_measurements (struct sht15_data*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t sht15_temp_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	int ret;
	struct sht15_data *data = dev_get_drvdata(dev);

	/* Technically no need to read humidity as well */
	ret = sht15_update_measurements(data);

	return ret ? ret : sprintf(buf, "%d\n",
				   sht15_calc_temp(data));
}