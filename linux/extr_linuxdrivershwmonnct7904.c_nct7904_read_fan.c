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
struct nct7904_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_0 ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FANIN1_HV_REG ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_fan_input 128 
 int nct7904_read_reg16 (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nct7904_read_fan(struct device *dev, u32 attr, int channel,
			    long *val)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	unsigned int cnt, rpm;
	int ret;

	switch (attr) {
	case hwmon_fan_input:
		ret = nct7904_read_reg16(data, BANK_0,
					 FANIN1_HV_REG + channel * 2);
		if (ret < 0)
			return ret;
		cnt = ((ret & 0xff00) >> 3) | (ret & 0x1f);
		if (cnt == 0x1fff)
			rpm = 0;
		else
			rpm = 1350000 / cnt;
		*val = rpm;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}