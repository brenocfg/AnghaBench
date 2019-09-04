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
struct ntc_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct ntc_data* dev_get_drvdata (struct device*) ; 
 int get_temp_mc (struct ntc_data*,int) ; 
 int ntc_thermistor_get_ohm (struct ntc_data*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t ntc_show_temp(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct ntc_data *data = dev_get_drvdata(dev);
	int ohm;

	ohm = ntc_thermistor_get_ohm(data);
	if (ohm < 0)
		return ohm;

	return sprintf(buf, "%d\n", get_temp_mc(data, ohm));
}