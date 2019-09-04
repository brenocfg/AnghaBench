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
struct rk3399_dmcfreq {int /*<<< orphan*/  dev; int /*<<< orphan*/  devfreq; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rk3399_dmcfreq* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_opp_of_remove_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_devfreq_unregister_opp_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk3399_dmcfreq_remove(struct platform_device *pdev)
{
	struct rk3399_dmcfreq *dmcfreq = dev_get_drvdata(&pdev->dev);

	/*
	 * Before remove the opp table we need to unregister the opp notifier.
	 */
	devm_devfreq_unregister_opp_notifier(dmcfreq->dev, dmcfreq->devfreq);
	dev_pm_opp_of_remove_table(dmcfreq->dev);

	return 0;
}