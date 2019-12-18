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
 int CC1_ITERM_60MA ; 
 int CC1_MODE_FASTCHARGE ; 
 int CC1_MODE_OFF ; 
 int CC1_VFCHG_4_2V ; 
 int CC2_ICHG_500MA ; 
 int CC3_270MIN_TIMEOUT ; 
 int CC4_BTEMP_MON_EN ; 
 int CC4_IFCHG_MON_EN ; 
 int CC6_BAT_OV_EN ; 
 int CC6_BAT_UV_EN ; 
 int CC6_UV_VBAT_SET ; 
 int CC7_BAT_REM_EN ; 
 int CC7_IFSM_EN ; 
 int /*<<< orphan*/  PM8606_PREREGULATORA ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL1 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL2 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL3 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL4 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL6 ; 
 int /*<<< orphan*/  PM8607_CHG_CTRL7 ; 
 int PREREG1_540MA ; 
 int PREREG1_VSYS_4_5V ; 
 int /*<<< orphan*/  VCHG_NORMAL_HIGH ; 
 int /*<<< orphan*/  VCHG_NORMAL_LOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int pm860x_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pm860x_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_vchg_threshold (struct pm860x_charger_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_fastcharge(struct pm860x_charger_info *info)
{
	int ret;

	dev_dbg(info->dev, "Start Fast-charging!\n");

	/* set fastcharge termination current & voltage, disable charging */
	ret = pm860x_reg_write(info->i2c, PM8607_CHG_CTRL1,
			       CC1_MODE_OFF | CC1_ITERM_60MA |
			       CC1_VFCHG_4_2V);
	if (ret < 0)
		goto out;
	ret = pm860x_reg_write(info->i2c_8606, PM8606_PREREGULATORA,
			       PREREG1_540MA | PREREG1_VSYS_4_5V);
	if (ret < 0)
		goto out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL2, 0x1f,
			      CC2_ICHG_500MA);
	if (ret < 0)
		goto out;
	/* set 270 minutes timeout */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL3, (0xf << 4),
			      CC3_270MIN_TIMEOUT);
	if (ret < 0)
		goto out;
	/* set IBAT & TBAT monitor */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL4,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN,
			      CC4_IFCHG_MON_EN | CC4_BTEMP_MON_EN);
	if (ret < 0)
		goto out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL6,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET,
			      CC6_BAT_OV_EN | CC6_BAT_UV_EN |
			      CC6_UV_VBAT_SET);
	if (ret < 0)
		goto out;
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL7,
			      CC7_BAT_REM_EN | CC7_IFSM_EN,
			      CC7_BAT_REM_EN | CC7_IFSM_EN);
	if (ret < 0)
		goto out;
	/* launch fast-charge */
	ret = pm860x_set_bits(info->i2c, PM8607_CHG_CTRL1, 3,
			      CC1_MODE_FASTCHARGE);
	/* vchg threshold setting */
	set_vchg_threshold(info, VCHG_NORMAL_LOW, VCHG_NORMAL_HIGH);
out:
	return ret;
}