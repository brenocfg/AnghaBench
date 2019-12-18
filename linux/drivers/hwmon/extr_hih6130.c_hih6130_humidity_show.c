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
struct hih6130 {int humidity; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct hih6130* dev_get_drvdata (struct device*) ; 
 int hih6130_update_measurements (struct device*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t hih6130_humidity_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct hih6130 *hih6130 = dev_get_drvdata(dev);
	int ret;

	ret = hih6130_update_measurements(dev);
	if (ret < 0)
		return ret;
	return sprintf(buf, "%d\n", hih6130->humidity);
}