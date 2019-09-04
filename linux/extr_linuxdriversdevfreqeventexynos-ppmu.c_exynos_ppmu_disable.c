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
 int /*<<< orphan*/  PPMU_CNTENC ; 
 int PPMU_PMCNT0_MASK ; 
 int PPMU_PMCNT1_MASK ; 
 int PPMU_PMCNT2_MASK ; 
 int PPMU_PMCNT3_MASK ; 
 int /*<<< orphan*/  PPMU_PMNC ; 
 int PPMU_PMNC_ENABLE_MASK ; 
 struct exynos_ppmu* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exynos_ppmu_disable(struct devfreq_event_dev *edev)
{
	struct exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	int ret;
	u32 pmnc;

	/* Disable all counters */
	ret = regmap_write(info->regmap, PPMU_CNTENC,
				PPMU_CCNT_MASK |
				PPMU_PMCNT0_MASK |
				PPMU_PMCNT1_MASK |
				PPMU_PMCNT2_MASK |
				PPMU_PMCNT3_MASK);
	if (ret < 0)
		return ret;

	/* Disable PPMU */
	ret = regmap_read(info->regmap, PPMU_PMNC, &pmnc);
	if (ret < 0)
		return ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_write(info->regmap, PPMU_PMNC, pmnc);
	if (ret < 0)
		return ret;

	return 0;
}