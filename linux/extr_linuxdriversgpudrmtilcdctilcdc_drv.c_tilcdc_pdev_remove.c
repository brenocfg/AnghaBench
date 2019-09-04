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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_master_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tilcdc_comp_ops ; 
 int /*<<< orphan*/  tilcdc_fini (int /*<<< orphan*/ ) ; 
 int tilcdc_get_external_components (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tilcdc_pdev_remove(struct platform_device *pdev)
{
	int ret;

	ret = tilcdc_get_external_components(&pdev->dev, NULL);
	if (ret < 0)
		return ret;
	else if (ret == 0)
		tilcdc_fini(platform_get_drvdata(pdev));
	else
		component_master_del(&pdev->dev, &tilcdc_comp_ops);

	return 0;
}