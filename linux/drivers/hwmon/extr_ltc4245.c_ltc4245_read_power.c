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
struct device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 long abs (unsigned long) ; 
#define  hwmon_power_input 128 
 int /*<<< orphan*/ * ltc4245_curr_regs ; 
 unsigned long ltc4245_get_current (struct device*,int /*<<< orphan*/ ) ; 
 long ltc4245_get_voltage (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ltc4245_in_regs ; 
 int /*<<< orphan*/  ltc4245_update_device (struct device*) ; 

__attribute__((used)) static int ltc4245_read_power(struct device *dev, u32 attr, int channel,
			      long *val)
{
	unsigned long curr;
	long voltage;

	switch (attr) {
	case hwmon_power_input:
		(void)ltc4245_update_device(dev);
		curr = ltc4245_get_current(dev, ltc4245_curr_regs[channel]);
		voltage = ltc4245_get_voltage(dev, ltc4245_in_regs[channel]);
		*val = abs(curr * voltage);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}