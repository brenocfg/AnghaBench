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
struct exynos_ppmu {int /*<<< orphan*/  regmap; } ;
struct devfreq_event_dev {int dummy; } ;

/* Variables and functions */
 int PPMU_CCNT_MASK ; 
 int PPMU_PMCNT0_MASK ; 
 int PPMU_PMCNT1_MASK ; 
 int PPMU_PMCNT2_MASK ; 
 int PPMU_PMCNT3_MASK ; 
 int PPMU_PMNC_ENABLE_MASK ; 
 int /*<<< orphan*/  PPMU_V2_CH_EV0_TYPE ; 
 int /*<<< orphan*/  PPMU_V2_CH_EV1_TYPE ; 
 int /*<<< orphan*/  PPMU_V2_CH_EV2_TYPE ; 
 int /*<<< orphan*/  PPMU_V2_CH_EV3_TYPE ; 
 int /*<<< orphan*/  PPMU_V2_CIG_CFG0 ; 
 int /*<<< orphan*/  PPMU_V2_CIG_CFG1 ; 
 int /*<<< orphan*/  PPMU_V2_CIG_CFG2 ; 
 int /*<<< orphan*/  PPMU_V2_CIG_RESULT ; 
 int /*<<< orphan*/  PPMU_V2_CNTENC ; 
 int /*<<< orphan*/  PPMU_V2_CNT_AUTO ; 
 int /*<<< orphan*/  PPMU_V2_CNT_RESET ; 
 int /*<<< orphan*/  PPMU_V2_FLAG ; 
 int /*<<< orphan*/  PPMU_V2_INTENC ; 
 int /*<<< orphan*/  PPMU_V2_INTERRUPT_RESET ; 
 int /*<<< orphan*/  PPMU_V2_PMNC ; 
 int /*<<< orphan*/  PPMU_V2_SM_ID_A ; 
 int /*<<< orphan*/  PPMU_V2_SM_ID_V ; 
 int /*<<< orphan*/  PPMU_V2_SM_OTHERS_A ; 
 int /*<<< orphan*/  PPMU_V2_SM_OTHERS_V ; 
 struct exynos_ppmu* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exynos_ppmu_v2_disable(struct devfreq_event_dev *edev)
{
	struct exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	int ret;
	u32 pmnc, clear;

	/* Disable all counters */
	clear = (PPMU_CCNT_MASK | PPMU_PMCNT0_MASK | PPMU_PMCNT1_MASK
		| PPMU_PMCNT2_MASK | PPMU_PMCNT3_MASK);
	ret = regmap_write(info->regmap, PPMU_V2_FLAG, clear);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_INTENC, clear);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CNTENC, clear);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CNT_RESET, clear);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CIG_CFG0, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CIG_CFG1, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CIG_CFG2, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CIG_RESULT, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CNT_AUTO, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CH_EV0_TYPE, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CH_EV1_TYPE, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CH_EV2_TYPE, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_CH_EV3_TYPE, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_SM_ID_V, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_SM_ID_A, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_SM_OTHERS_V, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_SM_OTHERS_A, 0x0);
	if (ret < 0)
		return ret;

	ret = regmap_write(info->regmap, PPMU_V2_INTERRUPT_RESET, 0x0);
	if (ret < 0)
		return ret;

	/* Disable PPMU */
	ret = regmap_read(info->regmap, PPMU_V2_PMNC, &pmnc);
	if (ret < 0)
		return ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_write(info->regmap, PPMU_V2_PMNC, pmnc);
	if (ret < 0)
		return ret;

	return 0;
}