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
struct tc654_data {int config; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct tc654_data*) ; 
 int /*<<< orphan*/  PTR_ERR (struct tc654_data*) ; 
 int TC654_REG_CONFIG_DUTYC ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct tc654_data* tc654_update_client (struct device*) ; 

__attribute__((used)) static ssize_t pwm_mode_show(struct device *dev, struct device_attribute *da,
			     char *buf)
{
	struct tc654_data *data = tc654_update_client(dev);

	if (IS_ERR(data))
		return PTR_ERR(data);

	return sprintf(buf, "%d\n", !!(data->config & TC654_REG_CONFIG_DUTYC));
}