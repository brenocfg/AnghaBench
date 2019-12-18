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
struct nct7904_data {int* vsen_alarm; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_0 ; 
 int /*<<< orphan*/  BANK_1 ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  SMI_STS1_REG ; 
 int /*<<< orphan*/  VSEN1_HV_HL_REG ; 
 int /*<<< orphan*/  VSEN1_HV_LL_REG ; 
 int /*<<< orphan*/  VSEN1_HV_REG ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_in_alarm 131 
#define  hwmon_in_input 130 
#define  hwmon_in_max 129 
#define  hwmon_in_min 128 
 int* nct7904_chan_to_index ; 
 int nct7904_read_reg (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nct7904_read_reg16 (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nct7904_read_in(struct device *dev, u32 attr, int channel,
			   long *val)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	int ret, volt, index;

	index = nct7904_chan_to_index[channel];

	switch (attr) {
	case hwmon_in_input:
		ret = nct7904_read_reg16(data, BANK_0,
					 VSEN1_HV_REG + index * 2);
		if (ret < 0)
			return ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		if (index < 14)
			volt *= 2; /* 0.002V scale */
		else
			volt *= 6; /* 0.006V scale */
		*val = volt;
		return 0;
	case hwmon_in_min:
		ret = nct7904_read_reg16(data, BANK_1,
					 VSEN1_HV_LL_REG + index * 4);
		if (ret < 0)
			return ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		if (index < 14)
			volt *= 2; /* 0.002V scale */
		else
			volt *= 6; /* 0.006V scale */
		*val = volt;
		return 0;
	case hwmon_in_max:
		ret = nct7904_read_reg16(data, BANK_1,
					 VSEN1_HV_HL_REG + index * 4);
		if (ret < 0)
			return ret;
		volt = ((ret & 0xff00) >> 5) | (ret & 0x7);
		if (index < 14)
			volt *= 2; /* 0.002V scale */
		else
			volt *= 6; /* 0.006V scale */
		*val = volt;
		return 0;
	case hwmon_in_alarm:
		ret = nct7904_read_reg(data, BANK_0,
				       SMI_STS1_REG + (index >> 3));
		if (ret < 0)
			return ret;
		if (!data->vsen_alarm[index >> 3])
			data->vsen_alarm[index >> 3] = ret & 0xff;
		else
			/* If there is new alarm showing up */
			data->vsen_alarm[index >> 3] |= (ret & 0xff);
		*val = (data->vsen_alarm[index >> 3] >> (index & 0x07)) & 1;
		/* Needs to clean the alarm if alarm existing */
		if (*val)
			data->vsen_alarm[index >> 3] ^= 1 << (index & 0x07);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}