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
typedef  int ssize_t ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int mc13783_adc_read (struct device*,struct device_attribute*,unsigned int*) ; 
 int sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static ssize_t mc13783_adc_gp_show(struct device *dev,
				   struct device_attribute *devattr,
				   char *buf)
{
	unsigned val;
	int ret = mc13783_adc_read(dev, devattr, &val);

	if (ret)
		return ret;

	/*
	 * input range is [0, 2.3V], val has 10 bits, so each bit
	 * is worth 9/4 mV.
	 */
	val = DIV_ROUND_CLOSEST(val * 9, 4);

	return sprintf(buf, "%u\n", val);
}