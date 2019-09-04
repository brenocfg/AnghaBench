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
struct fschmd_data {int global_control; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int FSCHMD_CONTROL_ALERT_LED ; 
 struct fschmd_data* fschmd_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t alert_led_show(struct device *dev,
	struct device_attribute *devattr, char *buf)
{
	struct fschmd_data *data = fschmd_update_device(dev);

	if (data->global_control & FSCHMD_CONTROL_ALERT_LED)
		return sprintf(buf, "1\n");
	else
		return sprintf(buf, "0\n");
}