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
typedef  int u32 ;
struct max31790_data {int fault_status; int /*<<< orphan*/ * target_count; int /*<<< orphan*/ * fan_dynamics; int /*<<< orphan*/ * tach; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct max31790_data*) ; 
 int PTR_ERR (struct max31790_data*) ; 
 int RPM_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int get_tach_period (int /*<<< orphan*/ ) ; 
#define  hwmon_fan_fault 130 
#define  hwmon_fan_input 129 
#define  hwmon_fan_target 128 
 struct max31790_data* max31790_update_device (struct device*) ; 

__attribute__((used)) static int max31790_read_fan(struct device *dev, u32 attr, int channel,
			     long *val)
{
	struct max31790_data *data = max31790_update_device(dev);
	int sr, rpm;

	if (IS_ERR(data))
		return PTR_ERR(data);

	switch (attr) {
	case hwmon_fan_input:
		sr = get_tach_period(data->fan_dynamics[channel]);
		rpm = RPM_FROM_REG(data->tach[channel], sr);
		*val = rpm;
		return 0;
	case hwmon_fan_target:
		sr = get_tach_period(data->fan_dynamics[channel]);
		rpm = RPM_FROM_REG(data->target_count[channel], sr);
		*val = rpm;
		return 0;
	case hwmon_fan_fault:
		*val = !!(data->fault_status & (1 << channel));
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}