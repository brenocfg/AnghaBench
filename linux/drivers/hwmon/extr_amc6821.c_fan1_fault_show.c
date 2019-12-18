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
struct amc6821_data {int stat1; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int AMC6821_STAT1_FANS ; 
 struct amc6821_data* amc6821_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t fan1_fault_show(struct device *dev,
			       struct device_attribute *devattr, char *buf)
{
	struct amc6821_data *data = amc6821_update_device(dev);
	if (data->stat1 & AMC6821_STAT1_FANS)
		return sprintf(buf, "1");
	else
		return sprintf(buf, "0");
}