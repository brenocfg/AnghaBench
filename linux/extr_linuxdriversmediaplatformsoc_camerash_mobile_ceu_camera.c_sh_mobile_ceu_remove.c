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
struct soc_camera_host {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  dma_release_declared_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_camera_host_unregister (struct soc_camera_host*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sh_mobile_ceu_remove(struct platform_device *pdev)
{
	struct soc_camera_host *soc_host = to_soc_camera_host(&pdev->dev);

	soc_camera_host_unregister(soc_host);
	pm_runtime_disable(&pdev->dev);
	if (platform_get_resource(pdev, IORESOURCE_MEM, 1))
		dma_release_declared_memory(&pdev->dev);

	return 0;
}