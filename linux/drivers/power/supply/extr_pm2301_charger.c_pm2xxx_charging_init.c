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
struct pm2xxx_charger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG3 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG4 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG5 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG6 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG7 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG8 ; 
 int /*<<< orphan*/  PM2XXX_BATT_CTRL_REG9 ; 
 int /*<<< orphan*/  PM2XXX_BATT_LOW_LEV_COMP_REG ; 
 int PM2XXX_CHARCHING_INFO_DIS ; 
 int PM2XXX_CH_150MV_DROP_300MV ; 
 int PM2XXX_CH_CC_MODEDROP_DIS ; 
 int PM2XXX_CH_CC_REDUCED_CURRENT_IDENT ; 
 int PM2XXX_CH_EOC_CURRENT_100MA ; 
 int PM2XXX_CH_PRECH_CURRENT_100MA ; 
 int PM2XXX_CH_PRECH_VOL_2_9 ; 
 int PM2XXX_CH_VOLT_4_2 ; 
 int PM2XXX_CH_VRESUME_VOL_3_8 ; 
 int PM2XXX_CH_WD_AUTO_TIMEOUT_20MIN ; 
 int PM2XXX_CH_WD_CC_PHASE_60MIN ; 
 int PM2XXX_CH_WD_CV_PHASE_60MIN ; 
 int PM2XXX_CH_WD_PRECH_PHASE_60MIN ; 
 int PM2XXX_DIR_CH_CC_CURRENT_1000MA ; 
 int /*<<< orphan*/  PM2XXX_INP_DROP_VPWR1 ; 
 int /*<<< orphan*/  PM2XXX_INP_DROP_VPWR2 ; 
 int /*<<< orphan*/  PM2XXX_INP_VOLT_VPWR1 ; 
 int /*<<< orphan*/  PM2XXX_INP_VOLT_VPWR2 ; 
 int PM2XXX_VBAT_LOW_MONITORING_ENA ; 
 int PM2XXX_VPWR1_DROP_DIS ; 
 int PM2XXX_VPWR1_HW_OPT_DIS ; 
 int PM2XXX_VPWR1_OVV_10 ; 
 int PM2XXX_VPWR1_VALID_DIS ; 
 int PM2XXX_VPWR2_DROP_DIS ; 
 int PM2XXX_VPWR2_HW_OPT_DIS ; 
 int PM2XXX_VPWR2_OVV_10 ; 
 int PM2XXX_VPWR2_VALID_DIS ; 
 int pm2xxx_reg_write (struct pm2xxx_charger*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm2xxx_charging_init(struct pm2xxx_charger *pm2)
{
	int ret = 0;

	/* enable CC and CV watchdog */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG3,
		(PM2XXX_CH_WD_CV_PHASE_60MIN | PM2XXX_CH_WD_CC_PHASE_60MIN));
	if( ret < 0)
		return ret;

	/* enable precharge watchdog */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG4,
					PM2XXX_CH_WD_PRECH_PHASE_60MIN);

	/* Disable auto timeout */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG5,
					PM2XXX_CH_WD_AUTO_TIMEOUT_20MIN);

	/*
     * EOC current level = 100mA
	 * Precharge current level = 100mA
	 * CC current level = 1000mA
	 */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG6,
		(PM2XXX_DIR_CH_CC_CURRENT_1000MA |
		PM2XXX_CH_PRECH_CURRENT_100MA |
		PM2XXX_CH_EOC_CURRENT_100MA));

	/*
     * recharge threshold = 3.8V
	 * Precharge to CC threshold = 2.9V
	 */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG7,
		(PM2XXX_CH_PRECH_VOL_2_9 | PM2XXX_CH_VRESUME_VOL_3_8));

	/* float voltage charger level = 4.2V */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG8,
		PM2XXX_CH_VOLT_4_2);

	/* Voltage drop between VBAT and VSYS in HW charging = 300mV */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_CTRL_REG9,
		(PM2XXX_CH_150MV_DROP_300MV | PM2XXX_CHARCHING_INFO_DIS |
		PM2XXX_CH_CC_REDUCED_CURRENT_IDENT |
		PM2XXX_CH_CC_MODEDROP_DIS));

	/* Input charger level of over voltage = 10V */
	ret = pm2xxx_reg_write(pm2, PM2XXX_INP_VOLT_VPWR2,
					PM2XXX_VPWR2_OVV_10);
	ret = pm2xxx_reg_write(pm2, PM2XXX_INP_VOLT_VPWR1,
					PM2XXX_VPWR1_OVV_10);

	/* Input charger drop */
	ret = pm2xxx_reg_write(pm2, PM2XXX_INP_DROP_VPWR2,
		(PM2XXX_VPWR2_HW_OPT_DIS | PM2XXX_VPWR2_VALID_DIS |
		PM2XXX_VPWR2_DROP_DIS));
	ret = pm2xxx_reg_write(pm2, PM2XXX_INP_DROP_VPWR1,
		(PM2XXX_VPWR1_HW_OPT_DIS | PM2XXX_VPWR1_VALID_DIS |
		PM2XXX_VPWR1_DROP_DIS));

	/* Disable battery low monitoring */
	ret = pm2xxx_reg_write(pm2, PM2XXX_BATT_LOW_LEV_COMP_REG,
		PM2XXX_VBAT_LOW_MONITORING_ENA);

	return ret;
}