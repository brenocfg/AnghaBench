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
struct ltc4245_data {int* cregs; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EOPNOTSUPP ; 
 size_t LTC4245_FAULT1 ; 
#define  hwmon_curr_input 129 
#define  hwmon_curr_max_alarm 128 
 int /*<<< orphan*/ * ltc4245_curr_regs ; 
 long ltc4245_get_current (struct device*,int /*<<< orphan*/ ) ; 
 struct ltc4245_data* ltc4245_update_device (struct device*) ; 

__attribute__((used)) static int ltc4245_read_curr(struct device *dev, u32 attr, int channel,
			     long *val)
{
	struct ltc4245_data *data = ltc4245_update_device(dev);

	switch (attr) {
	case hwmon_curr_input:
		*val = ltc4245_get_current(dev, ltc4245_curr_regs[channel]);
		return 0;
	case hwmon_curr_max_alarm:
		*val = !!(data->cregs[LTC4245_FAULT1] & BIT(channel + 4));
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}