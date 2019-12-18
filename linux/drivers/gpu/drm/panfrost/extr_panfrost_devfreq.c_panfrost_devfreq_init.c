#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct dev_pm_opp* devfreq; int /*<<< orphan*/  cur_freq; } ;
struct panfrost_device {TYPE_2__* pdev; TYPE_1__ devfreq; int /*<<< orphan*/  clock; } ;
struct dev_pm_opp {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  initial_freq; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_SIMPLE_ONDEMAND ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 int PTR_ERR (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int dev_pm_opp_of_add_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 struct dev_pm_opp* devfreq_recommended_opp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dev_pm_opp* devm_devfreq_add_device (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ panfrost_devfreq_profile ; 
 int /*<<< orphan*/  panfrost_devfreq_reset (struct panfrost_device*) ; 

int panfrost_devfreq_init(struct panfrost_device *pfdev)
{
	int ret;
	struct dev_pm_opp *opp;

	ret = dev_pm_opp_of_add_table(&pfdev->pdev->dev);
	if (ret == -ENODEV) /* Optional, continue without devfreq */
		return 0;
	else if (ret)
		return ret;

	panfrost_devfreq_reset(pfdev);

	pfdev->devfreq.cur_freq = clk_get_rate(pfdev->clock);

	opp = devfreq_recommended_opp(&pfdev->pdev->dev, &pfdev->devfreq.cur_freq, 0);
	if (IS_ERR(opp))
		return PTR_ERR(opp);

	panfrost_devfreq_profile.initial_freq = pfdev->devfreq.cur_freq;
	dev_pm_opp_put(opp);

	pfdev->devfreq.devfreq = devm_devfreq_add_device(&pfdev->pdev->dev,
			&panfrost_devfreq_profile, DEVFREQ_GOV_SIMPLE_ONDEMAND,
			NULL);
	if (IS_ERR(pfdev->devfreq.devfreq)) {
		DRM_DEV_ERROR(&pfdev->pdev->dev, "Couldn't initialize GPU devfreq\n");
		ret = PTR_ERR(pfdev->devfreq.devfreq);
		pfdev->devfreq.devfreq = NULL;
		dev_pm_opp_of_remove_table(&pfdev->pdev->dev);
		return ret;
	}

	return 0;
}