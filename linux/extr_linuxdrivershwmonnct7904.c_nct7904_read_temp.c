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
 int /*<<< orphan*/  LTD_HV_REG ; 
 int /*<<< orphan*/  T_CPU1_HV_REG ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_input 128 
 int nct7904_read_reg16 (struct nct7904_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,int) ; 

__attribute__((used)) static int nct7904_read_temp(struct device *dev, u32 attr, int channel,
			     long *val)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	int ret, temp;

	switch (attr) {
	case hwmon_temp_input:
		if (channel == 0)
			ret = nct7904_read_reg16(data, BANK_0, LTD_HV_REG);
		else
			ret = nct7904_read_reg16(data, BANK_0,
					T_CPU1_HV_REG + (channel - 1) * 2);
		if (ret < 0)
			return ret;
		temp = ((ret & 0xff00) >> 5) | (ret & 0x7);
		*val = sign_extend32(temp, 10) * 125;
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}