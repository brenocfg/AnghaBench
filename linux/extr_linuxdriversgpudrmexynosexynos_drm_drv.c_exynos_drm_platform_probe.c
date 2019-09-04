#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  coherent_dma_mask; } ;
struct platform_device {TYPE_1__ dev; } ;
struct component_match {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ IS_ERR (struct component_match*) ; 
 int PTR_ERR (struct component_match*) ; 
 int component_master_add_with_match (TYPE_1__*,int /*<<< orphan*/ *,struct component_match*) ; 
 struct component_match* exynos_drm_match_add (TYPE_1__*) ; 
 int /*<<< orphan*/  exynos_drm_ops ; 

__attribute__((used)) static int exynos_drm_platform_probe(struct platform_device *pdev)
{
	struct component_match *match;

	pdev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	match = exynos_drm_match_add(&pdev->dev);
	if (IS_ERR(match))
		return PTR_ERR(match);

	return component_master_add_with_match(&pdev->dev, &exynos_drm_ops,
					       match);
}