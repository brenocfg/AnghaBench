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
struct component_match {int dummy; } ;

/* Variables and functions */
 int add_display_components (int /*<<< orphan*/ *,struct component_match**) ; 
 int add_gpu_components (int /*<<< orphan*/ *,struct component_match**) ; 
 int component_master_add_with_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct component_match*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_mdp_ver (struct platform_device*) ; 
 int /*<<< orphan*/  msm_drm_ops ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msm_pdev_probe(struct platform_device *pdev)
{
	struct component_match *match = NULL;
	int ret;

	if (get_mdp_ver(pdev)) {
		ret = add_display_components(&pdev->dev, &match);
		if (ret)
			return ret;
	}

	ret = add_gpu_components(&pdev->dev, &match);
	if (ret)
		goto fail;

	/* on all devices that I am aware of, iommu's which can map
	 * any address the cpu can see are used:
	 */
	ret = dma_set_mask_and_coherent(&pdev->dev, ~0);
	if (ret)
		goto fail;

	ret = component_master_add_with_match(&pdev->dev, &msm_drm_ops, match);
	if (ret)
		goto fail;

	return 0;

fail:
	of_platform_depopulate(&pdev->dev);
	return ret;
}