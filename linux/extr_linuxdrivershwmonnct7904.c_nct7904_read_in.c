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
 int /*<<< orphan*/  VSEN1_HV_REG ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_in_input 128 
 int* nct7904_chan_to_index ; 
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
	default:
		return -EOPNOTSUPP;
	}
}