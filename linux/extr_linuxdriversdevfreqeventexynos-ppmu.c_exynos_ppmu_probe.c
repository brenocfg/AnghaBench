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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;
struct exynos_ppmu {int num_events; TYPE_1__ ppmu; struct devfreq_event_dev** edev; struct devfreq_event_desc* desc; int /*<<< orphan*/ * dev; } ;
struct devfreq_event_dev {int dummy; } ;
struct devfreq_event_desc {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct devfreq_event_dev*) ; 
 int PTR_ERR (struct devfreq_event_dev*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct devfreq_event_dev* devm_devfreq_event_add_edev (int /*<<< orphan*/ *,struct devfreq_event_desc*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int exynos_ppmu_parse_dt (struct platform_device*,struct exynos_ppmu*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_ppmu*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_ppmu_probe(struct platform_device *pdev)
{
	struct exynos_ppmu *info;
	struct devfreq_event_dev **edev;
	struct devfreq_event_desc *desc;
	int i, ret = 0, size;

	info = devm_kzalloc(&pdev->dev, sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->dev = &pdev->dev;

	/* Parse dt data to get resource */
	ret = exynos_ppmu_parse_dt(pdev, info);
	if (ret < 0) {
		dev_err(&pdev->dev,
			"failed to parse devicetree for resource\n");
		return ret;
	}
	desc = info->desc;

	size = sizeof(struct devfreq_event_dev *) * info->num_events;
	info->edev = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	if (!info->edev)
		return -ENOMEM;

	edev = info->edev;
	platform_set_drvdata(pdev, info);

	for (i = 0; i < info->num_events; i++) {
		edev[i] = devm_devfreq_event_add_edev(&pdev->dev, &desc[i]);
		if (IS_ERR(edev[i])) {
			ret = PTR_ERR(edev[i]);
			dev_err(&pdev->dev,
				"failed to add devfreq-event device\n");
			return PTR_ERR(edev[i]);
		}

		pr_info("exynos-ppmu: new PPMU device registered %s (%s)\n",
			dev_name(&pdev->dev), desc[i].name);
	}

	ret = clk_prepare_enable(info->ppmu.clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to prepare ppmu clock\n");
		return ret;
	}

	return 0;
}