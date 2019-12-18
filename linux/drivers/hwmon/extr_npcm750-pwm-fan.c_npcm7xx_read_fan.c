#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct npcm7xx_pwm_fan_data {int input_clk_freq; TYPE_1__* fan_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int fan_cnt; int fan_pls_per_rev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct npcm7xx_pwm_fan_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_fan_input 128 

__attribute__((used)) static int npcm7xx_read_fan(struct device *dev, u32 attr, int channel,
			    long *val)
{
	struct npcm7xx_pwm_fan_data *data = dev_get_drvdata(dev);

	switch (attr) {
	case hwmon_fan_input:
		*val = 0;
		if (data->fan_dev[channel].fan_cnt <= 0)
			return data->fan_dev[channel].fan_cnt;

		/* Convert the raw reading to RPM */
		if (data->fan_dev[channel].fan_cnt > 0 &&
		    data->fan_dev[channel].fan_pls_per_rev > 0)
			*val = ((data->input_clk_freq * 60) /
				(data->fan_dev[channel].fan_cnt *
				 data->fan_dev[channel].fan_pls_per_rev));
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}