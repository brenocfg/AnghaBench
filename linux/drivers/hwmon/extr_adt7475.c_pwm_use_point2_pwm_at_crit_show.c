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
struct adt7475_data {int config4; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int CONFIG4_MAXDUTY ; 
 scalar_t__ IS_ERR (struct adt7475_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct adt7475_data*) ; 
 struct adt7475_data* adt7475_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t pwm_use_point2_pwm_at_crit_show(struct device *dev,
					struct device_attribute *devattr,
					char *buf)
{
	struct adt7475_data *data = adt7475_update_device(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	return sprintf(buf, "%d\n", !!(data->config4 & CONFIG4_MAXDUTY));
}