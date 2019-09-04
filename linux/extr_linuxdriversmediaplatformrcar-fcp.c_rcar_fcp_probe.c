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
struct rcar_fcp_device {int /*<<< orphan*/  list; int /*<<< orphan*/ * dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rcar_fcp_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcp_devices ; 
 int /*<<< orphan*/  fcp_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_fcp_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_fcp_probe(struct platform_device *pdev)
{
	struct rcar_fcp_device *fcp;

	fcp = devm_kzalloc(&pdev->dev, sizeof(*fcp), GFP_KERNEL);
	if (fcp == NULL)
		return -ENOMEM;

	fcp->dev = &pdev->dev;

	pm_runtime_enable(&pdev->dev);

	mutex_lock(&fcp_lock);
	list_add_tail(&fcp->list, &fcp_devices);
	mutex_unlock(&fcp_lock);

	platform_set_drvdata(pdev, fcp);

	return 0;
}