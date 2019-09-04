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
struct emc2103_data {int fan_tach; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct emc2103_data* emc2103_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
fan1_fault_show(struct device *dev, struct device_attribute *da, char *buf)
{
	struct emc2103_data *data = emc2103_update_device(dev);
	bool fault = ((data->fan_tach & 0x1fe0) == 0x1fe0);
	return sprintf(buf, "%d\n", fault ? 1 : 0);
}