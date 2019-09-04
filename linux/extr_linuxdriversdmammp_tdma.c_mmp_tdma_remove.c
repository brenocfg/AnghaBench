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
struct platform_device {int dummy; } ;
struct mmp_tdma_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (int /*<<< orphan*/ *) ; 
 struct mmp_tdma_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mmp_tdma_remove(struct platform_device *pdev)
{
	struct mmp_tdma_device *tdev = platform_get_drvdata(pdev);

	dma_async_device_unregister(&tdev->device);
	return 0;
}