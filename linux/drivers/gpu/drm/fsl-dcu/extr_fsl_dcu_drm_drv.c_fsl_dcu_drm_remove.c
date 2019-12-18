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
struct fsl_dcu_drm_device {int /*<<< orphan*/  pix_clk; int /*<<< orphan*/  clk; int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_unregister (int /*<<< orphan*/ ) ; 
 struct fsl_dcu_drm_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int fsl_dcu_drm_remove(struct platform_device *pdev)
{
	struct fsl_dcu_drm_device *fsl_dev = platform_get_drvdata(pdev);

	drm_dev_unregister(fsl_dev->drm);
	drm_dev_put(fsl_dev->drm);
	clk_disable_unprepare(fsl_dev->clk);
	clk_unregister(fsl_dev->pix_clk);

	return 0;
}