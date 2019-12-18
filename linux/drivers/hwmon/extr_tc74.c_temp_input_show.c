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
struct tc74_data {int temp_input; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct tc74_data* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int tc74_update_device (struct device*) ; 

__attribute__((used)) static ssize_t temp_input_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct tc74_data *data = dev_get_drvdata(dev);
	int ret;

	ret = tc74_update_device(dev);
	if (ret)
		return ret;

	return sprintf(buf, "%d\n", data->temp_input * 1000);
}