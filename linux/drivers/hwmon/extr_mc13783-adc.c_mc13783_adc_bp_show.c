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
struct platform_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int kernel_ulong_t ;
struct TYPE_2__ {int driver_data; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int MC13783_ADC_BPDIV2 ; 
 int mc13783_adc_read (struct device*,struct device_attribute*,unsigned int*) ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 
 int sprintf (char*,char*,unsigned int) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t mc13783_adc_bp_show(struct device *dev,
				   struct device_attribute *devattr,
				   char *buf)
{
	unsigned val;
	struct platform_device *pdev = to_platform_device(dev);
	kernel_ulong_t driver_data = platform_get_device_id(pdev)->driver_data;
	int ret = mc13783_adc_read(dev, devattr, &val);

	if (ret)
		return ret;

	if (driver_data & MC13783_ADC_BPDIV2)
		val = DIV_ROUND_CLOSEST(val * 9, 2);
	else
		/*
		 * BP (channel 2) reports with offset 2.4V to the actual value
		 * to fit the input range of the ADC.  unit = 2.25mV = 9/4 mV.
		 */
		val = DIV_ROUND_CLOSEST(val * 9, 4) + 2400;

	return sprintf(buf, "%u\n", val);
}