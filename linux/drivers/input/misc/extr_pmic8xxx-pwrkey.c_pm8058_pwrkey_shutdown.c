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
typedef  int u8 ;
struct regmap {int dummy; } ;
struct pmic8xxx_pwrkey {struct regmap* regmap; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  PM8058_L21_CTRL ; 
 int /*<<< orphan*/  PM8058_L22_CTRL ; 
 int /*<<< orphan*/  PM8058_S0_CTRL ; 
 int /*<<< orphan*/  PM8058_S0_TEST2 ; 
 int /*<<< orphan*/  PM8058_S1_CTRL ; 
 int /*<<< orphan*/  PM8058_S1_TEST2 ; 
 int /*<<< orphan*/  PM8058_S3_CTRL ; 
 int /*<<< orphan*/  PM8058_S3_TEST2 ; 
 int /*<<< orphan*/  PM8058_SLEEP_CTRL ; 
 int /*<<< orphan*/  REG_PM8058_VREG_EN_GRP_5_4 ; 
 int /*<<< orphan*/  REG_PM8058_VREG_EN_MSM ; 
 int SLEEP_CTRL_SMPL_EN_RESET ; 
 int /*<<< orphan*/  pm8058_disable_ldo_locally_set_pull_down (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm8058_disable_smps_locally_set_pull_down (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pm8058_pwrkey_shutdown(struct pmic8xxx_pwrkey *pwrkey, bool reset)
{
	int error;
	struct regmap *regmap = pwrkey->regmap;
	u8 mask, val;

	/* When shutting down, enable active pulldowns on important rails. */
	if (!reset) {
		/* Disable SMPS's 0,1,3 locally and set pulldown enable bits. */
		pm8058_disable_smps_locally_set_pull_down(regmap,
			PM8058_S0_CTRL, PM8058_S0_TEST2,
			REG_PM8058_VREG_EN_MSM, BIT(7));
		pm8058_disable_smps_locally_set_pull_down(regmap,
			PM8058_S1_CTRL, PM8058_S1_TEST2,
			REG_PM8058_VREG_EN_MSM, BIT(6));
		pm8058_disable_smps_locally_set_pull_down(regmap,
			PM8058_S3_CTRL, PM8058_S3_TEST2,
			REG_PM8058_VREG_EN_GRP_5_4, BIT(7) | BIT(4));
		/* Disable LDO 21 locally and set pulldown enable bit. */
		pm8058_disable_ldo_locally_set_pull_down(regmap,
			PM8058_L21_CTRL, REG_PM8058_VREG_EN_GRP_5_4,
			BIT(1));
	}

	/*
	 * Fix-up: Set regulator LDO22 to 1.225 V in high power mode. Leave its
	 * pull-down state intact. This ensures a safe shutdown.
	 */
	error = regmap_update_bits(regmap, PM8058_L22_CTRL, 0xbf, 0x93);
	if (error)
		return error;

	/* Enable SMPL if resetting is desired */
	mask = SLEEP_CTRL_SMPL_EN_RESET;
	val = 0;
	if (reset)
		val = mask;
	return regmap_update_bits(regmap, PM8058_SLEEP_CTRL, mask, val);
}