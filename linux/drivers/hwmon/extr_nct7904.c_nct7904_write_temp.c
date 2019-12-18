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
 int /*<<< orphan*/  BANK_1 ; 
 unsigned int DTS_T_CPU1_CH_REG ; 
 unsigned int DTS_T_CPU1_C_REG ; 
 unsigned int DTS_T_CPU1_WH_REG ; 
 unsigned int DTS_T_CPU1_W_REG ; 
 int EOPNOTSUPP ; 
 unsigned int LTD_HV_HL_REG ; 
 unsigned int LTD_HV_LL_REG ; 
 unsigned int LTD_LV_HL_REG ; 
 unsigned int LTD_LV_LL_REG ; 
 unsigned int TEMP_CH1_CH_REG ; 
 unsigned int TEMP_CH1_C_REG ; 
 unsigned int TEMP_CH1_WH_REG ; 
 unsigned int TEMP_CH1_W_REG ; 
 long clamp_val (long,int,int) ; 
 struct nct7904_data* dev_get_drvdata (struct device*) ; 
#define  hwmon_temp_crit 131 
#define  hwmon_temp_crit_hyst 130 
#define  hwmon_temp_max 129 
#define  hwmon_temp_max_hyst 128 
 int nct7904_write_reg (struct nct7904_data*,int /*<<< orphan*/ ,unsigned int,long) ; 

__attribute__((used)) static int nct7904_write_temp(struct device *dev, u32 attr, int channel,
			      long val)
{
	struct nct7904_data *data = dev_get_drvdata(dev);
	int ret;
	unsigned int reg1, reg2, reg3;

	val = clamp_val(val / 1000, -128, 127);

	switch (attr) {
	case hwmon_temp_max:
		reg1 = LTD_HV_LL_REG;
		reg2 = TEMP_CH1_W_REG;
		reg3 = DTS_T_CPU1_W_REG;
		break;
	case hwmon_temp_max_hyst:
		reg1 = LTD_LV_LL_REG;
		reg2 = TEMP_CH1_WH_REG;
		reg3 = DTS_T_CPU1_WH_REG;
		break;
	case hwmon_temp_crit:
		reg1 = LTD_HV_HL_REG;
		reg2 = TEMP_CH1_C_REG;
		reg3 = DTS_T_CPU1_C_REG;
		break;
	case hwmon_temp_crit_hyst:
		reg1 = LTD_LV_HL_REG;
		reg2 = TEMP_CH1_CH_REG;
		reg3 = DTS_T_CPU1_CH_REG;
		break;
	default:
		return -EOPNOTSUPP;
	}
	if (channel == 4)
		ret = nct7904_write_reg(data, BANK_1, reg1, val);
	else if (channel < 5)
		ret = nct7904_write_reg(data, BANK_1,
					reg2 + channel * 8, val);
	else
		ret = nct7904_write_reg(data, BANK_1,
					reg3 + (channel - 5) * 4, val);

	return ret;
}