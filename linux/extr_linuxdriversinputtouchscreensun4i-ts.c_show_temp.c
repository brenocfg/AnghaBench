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
struct sun4i_ts_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct sun4i_ts_data* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int sun4i_get_temp (struct sun4i_ts_data*,int*) ; 

__attribute__((used)) static ssize_t show_temp(struct device *dev, struct device_attribute *devattr,
			 char *buf)
{
	struct sun4i_ts_data *ts = dev_get_drvdata(dev);
	int temp;
	int error;

	error = sun4i_get_temp(ts, &temp);
	if (error)
		return error;

	return sprintf(buf, "%d\n", temp);
}