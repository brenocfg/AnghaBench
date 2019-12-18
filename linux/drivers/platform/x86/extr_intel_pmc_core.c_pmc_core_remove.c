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
struct pmc_dev {int /*<<< orphan*/  regbase; int /*<<< orphan*/  lock; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct pmc_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_core_dbgfs_unregister (struct pmc_dev*) ; 

__attribute__((used)) static int pmc_core_remove(struct platform_device *pdev)
{
	struct pmc_dev *pmcdev = platform_get_drvdata(pdev);

	pmc_core_dbgfs_unregister(pmcdev);
	platform_set_drvdata(pdev, NULL);
	mutex_destroy(&pmcdev->lock);
	iounmap(pmcdev->regbase);
	return 0;
}