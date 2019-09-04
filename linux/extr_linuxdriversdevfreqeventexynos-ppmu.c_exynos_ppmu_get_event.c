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
struct exynos_ppmu {int /*<<< orphan*/  regmap; } ;
struct devfreq_event_dev {TYPE_1__* desc; int /*<<< orphan*/  dev; } ;
struct devfreq_event_data {unsigned int total_count; unsigned int load_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PPMU_CCNT ; 
 int PPMU_CCNT_MASK ; 
 int /*<<< orphan*/  PPMU_CNTENC ; 
 int PPMU_ENABLE ; 
 int /*<<< orphan*/  PPMU_PMCNT3_HIGH ; 
 int /*<<< orphan*/  PPMU_PMCNT3_LOW ; 
 int /*<<< orphan*/  PPMU_PMNC ; 
#define  PPMU_PMNCNT0 131 
#define  PPMU_PMNCNT1 130 
#define  PPMU_PMNCNT2 129 
#define  PPMU_PMNCNT3 128 
 int /*<<< orphan*/  PPMU_PMNCT (int) ; 
 unsigned int PPMU_PMNC_ENABLE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct exynos_ppmu* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int exynos_ppmu_find_ppmu_id (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int exynos_ppmu_get_event(struct devfreq_event_dev *edev,
				struct devfreq_event_data *edata)
{
	struct exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	int id = exynos_ppmu_find_ppmu_id(edev);
	unsigned int total_count, load_count;
	unsigned int pmcnt3_high, pmcnt3_low;
	unsigned int pmnc, cntenc;
	int ret;

	if (id < 0)
		return -EINVAL;

	/* Disable PPMU */
	ret = regmap_read(info->regmap, PPMU_PMNC, &pmnc);
	if (ret < 0)
		return ret;

	pmnc &= ~PPMU_PMNC_ENABLE_MASK;
	ret = regmap_write(info->regmap, PPMU_PMNC, pmnc);
	if (ret < 0)
		return ret;

	/* Read cycle count */
	ret = regmap_read(info->regmap, PPMU_CCNT, &total_count);
	if (ret < 0)
		return ret;
	edata->total_count = total_count;

	/* Read performance count */
	switch (id) {
	case PPMU_PMNCNT0:
	case PPMU_PMNCNT1:
	case PPMU_PMNCNT2:
		ret = regmap_read(info->regmap, PPMU_PMNCT(id), &load_count);
		if (ret < 0)
			return ret;
		edata->load_count = load_count;
		break;
	case PPMU_PMNCNT3:
		ret = regmap_read(info->regmap, PPMU_PMCNT3_HIGH, &pmcnt3_high);
		if (ret < 0)
			return ret;

		ret = regmap_read(info->regmap, PPMU_PMCNT3_LOW, &pmcnt3_low);
		if (ret < 0)
			return ret;

		edata->load_count = ((pmcnt3_high << 8) | pmcnt3_low);
		break;
	default:
		return -EINVAL;
	}

	/* Disable specific counter */
	ret = regmap_read(info->regmap, PPMU_CNTENC, &cntenc);
	if (ret < 0)
		return ret;

	cntenc |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_write(info->regmap, PPMU_CNTENC, cntenc);
	if (ret < 0)
		return ret;

	dev_dbg(&edev->dev, "%s (event: %ld/%ld)\n", edev->desc->name,
					edata->load_count, edata->total_count);

	return 0;
}