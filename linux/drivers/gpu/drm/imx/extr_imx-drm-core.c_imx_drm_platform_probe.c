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
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  compare_of ; 
 int dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_of_component_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  imx_drm_ops ; 

__attribute__((used)) static int imx_drm_platform_probe(struct platform_device *pdev)
{
	int ret = drm_of_component_probe(&pdev->dev, compare_of, &imx_drm_ops);

	if (!ret)
		ret = dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	return ret;
}