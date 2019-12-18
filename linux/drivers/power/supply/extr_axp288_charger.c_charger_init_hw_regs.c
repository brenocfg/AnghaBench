#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct axp288_chrg_info {int cc; int max_cc; int /*<<< orphan*/  cv; int /*<<< orphan*/  max_cv; TYPE_1__* pdev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CC_CTRL ; 
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int /*<<< orphan*/  AXP20X_CHRG_CTRL2 ; 
 int /*<<< orphan*/  AXP20X_V_HTF_CHRG ; 
 int /*<<< orphan*/  AXP20X_V_LTF_CHRG ; 
 unsigned int CHRG_CCCV_CC_BIT_POS ; 
 int CHRG_CCCV_CC_LSB_RES ; 
 unsigned int CHRG_CCCV_CC_MASK ; 
 int CHRG_CCCV_CC_OFFSET ; 
#define  CHRG_CCCV_CV_4100MV 131 
#define  CHRG_CCCV_CV_4150MV 130 
#define  CHRG_CCCV_CV_4200MV 129 
#define  CHRG_CCCV_CV_4350MV 128 
 unsigned int CHRG_CCCV_CV_BIT_POS ; 
 unsigned int CHRG_CCCV_CV_MASK ; 
 int /*<<< orphan*/  CHRG_CCCV_ITERM_20P ; 
 int /*<<< orphan*/  CHRG_VHTFC_45C ; 
 int /*<<< orphan*/  CHRG_VLTFC_0C ; 
 int /*<<< orphan*/  CNTL2_CHG_OUT_TURNON ; 
 int /*<<< orphan*/  CV_4100MV ; 
 int /*<<< orphan*/  CV_4150MV ; 
 int /*<<< orphan*/  CV_4200MV ; 
 int /*<<< orphan*/  CV_4350MV ; 
 int /*<<< orphan*/  FG_CNTL_OCV_ADJ_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int charger_init_hw_regs(struct axp288_chrg_info *info)
{
	int ret, cc, cv;
	unsigned int val;

	/* Program temperature thresholds */
	ret = regmap_write(info->regmap, AXP20X_V_LTF_CHRG, CHRG_VLTFC_0C);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
							AXP20X_V_LTF_CHRG, ret);
		return ret;
	}

	ret = regmap_write(info->regmap, AXP20X_V_HTF_CHRG, CHRG_VHTFC_45C);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
							AXP20X_V_HTF_CHRG, ret);
		return ret;
	}

	/* Do not turn-off charger o/p after charge cycle ends */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL2,
				CNTL2_CHG_OUT_TURNON, CNTL2_CHG_OUT_TURNON);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CHRG_CTRL2, ret);
		return ret;
	}

	/* Setup ending condition for charging to be 10% of I(chrg) */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CHRG_CTRL1,
				CHRG_CCCV_ITERM_20P, 0);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CHRG_CTRL1, ret);
		return ret;
	}

	/* Disable OCV-SOC curve calibration */
	ret = regmap_update_bits(info->regmap,
				AXP20X_CC_CTRL,
				FG_CNTL_OCV_ADJ_EN, 0);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) write error(%d)\n",
						AXP20X_CC_CTRL, ret);
		return ret;
	}

	/* Read current charge voltage and current limit */
	ret = regmap_read(info->regmap, AXP20X_CHRG_CTRL1, &val);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "register(%x) read error(%d)\n",
			AXP20X_CHRG_CTRL1, ret);
		return ret;
	}

	/* Determine charge voltage */
	cv = (val & CHRG_CCCV_CV_MASK) >> CHRG_CCCV_CV_BIT_POS;
	switch (cv) {
	case CHRG_CCCV_CV_4100MV:
		info->cv = CV_4100MV;
		break;
	case CHRG_CCCV_CV_4150MV:
		info->cv = CV_4150MV;
		break;
	case CHRG_CCCV_CV_4200MV:
		info->cv = CV_4200MV;
		break;
	case CHRG_CCCV_CV_4350MV:
		info->cv = CV_4350MV;
		break;
	}

	/* Determine charge current limit */
	cc = (val & CHRG_CCCV_CC_MASK) >> CHRG_CCCV_CC_BIT_POS;
	cc = (cc * CHRG_CCCV_CC_LSB_RES) + CHRG_CCCV_CC_OFFSET;
	info->cc = cc;

	/*
	 * Do not allow the user to configure higher settings then those
	 * set by the firmware
	 */
	info->max_cv = info->cv;
	info->max_cc = info->cc;

	return 0;
}