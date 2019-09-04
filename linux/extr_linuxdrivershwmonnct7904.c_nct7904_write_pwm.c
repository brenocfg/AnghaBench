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
struct nct7904_data {long* fan_mode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_3 ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FANCTL1_FMR_REG ; 
 int /*<<< orphan*/  FANCTL1_OUT_REG ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_pwm_enable 129 
#define  hwmon_pwm_input 128 
 int nct7904_write_reg (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int nct7904_write_pwm(struct device *dev, u32 attr, int channel,
			     long val)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	int ret;

	switch (attr) {
	case hwmon_pwm_input:
		if (val < 0 || val > 255)
			return -EINVAL;
		ret = nct7904_write_reg(data, BANK_3, FANCTL1_OUT_REG + channel,
					val);
		return ret;
	case hwmon_pwm_enable:
		if (val < 1 || val > 2 ||
		    (val == 2 && !data->fan_mode[channel]))
			return -EINVAL;
		ret = nct7904_write_reg(data, BANK_3, FANCTL1_FMR_REG + channel,
					val == 2 ? data->fan_mode[channel] : 0);
		return ret;
	default:
		return -EOPNOTSUPP;
	}
}