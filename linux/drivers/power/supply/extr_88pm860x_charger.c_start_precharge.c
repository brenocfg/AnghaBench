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
struct pm860x_charger_info {int /*<<< orphan*/  i2c; int /*<<< orphan*/  i2c_8606; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CC1_MODE_OFF ; 
 int CC1_MODE_PRECHARGE ; 
 int CC3_270MIN_TIMEOUT ; 
 int CC4_BTEMP_MON_EN ; 
 int CC4_IFCHG_MON_EN ; 
 int CC4_IPRE_40MA ; 
 int CC4_VPCHG_3_2V ; 
 int CC7_BAT_REM_EN ; 
 int CC7_IFSM_EN ; 
 int /*<<< orphan*/  PM8606_PREREGULATORA ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL1 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL3 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL4 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL7 ; 
 int PREREG1_1350MA ; 
 int PREREG1_VSYS_4_5V ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int pm860x_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_vbatt_threshold (struct pm860x_charger_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_precharge(struct pm860x_charger_info *info)
{
	int ret;

	dev_dbg(info->dev, "Start Pre-charging!\n");
	set_vbatt_threshold(info, 0, 0);

	ret = pm860x_reg_write(info->i2c_8606, PM8606_PREREGULATORA,
			       PREREG1_1350MA | PREREG1_VSYS_4_5V);
	if (ret < 0)
		goto out;
	/* stop charging */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_OFF);
	if (ret < 0)
		goto out;
	/* set 270 minutes timeout */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	if (ret < 0)
		goto out;
	/* set precharge current, termination voltage, IBAT & TBAT monitor */
	ret = pm860x_reg_write(info->i2c, PM8607_CHG_CTRL4,
			       CC4_IPRE_40MA | CC4_VPCHG_3_2V |
			       CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	if (ret < 0)
		goto out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL7,
			      CC7_BAT_REM_EN | CC7_IFSM_EN,
			      CC7_BAT_REM_EN | CC7_IFSM_EN);
	if (ret < 0)
		goto out;
	/* trigger precharge */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_PRECHARGE);
out:
	return ret;
}