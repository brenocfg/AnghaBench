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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  num_resources; int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 struct platform_device* ci_hdrc_add_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ci_hdrc_zevio_platdata ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct platform_device*) ; 

__attribute__((used)) static int ci_hdrc_zevio_probe(struct platform_device *pdev)
{
	struct platform_device *ci_pdev;

	dev_dbg(&pdev->dev, "ci_hdrc_zevio_probe\n");

	ci_pdev = ci_hdrc_add_device(&pdev->dev,
				pdev->resource, pdev->num_resources,
				&ci_hdrc_zevio_platdata);

	if (IS_ERR(ci_pdev)) {
		dev_err(&pdev->dev, "ci_hdrc_add_device failed!\n");
		return PTR_ERR(ci_pdev);
	}

	platform_set_drvdata(pdev, ci_pdev);

	return 0;
}