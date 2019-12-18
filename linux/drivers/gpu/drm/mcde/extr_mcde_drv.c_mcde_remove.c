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
struct mcde {int /*<<< orphan*/  epod; int /*<<< orphan*/  vana; int /*<<< orphan*/  mcde_clk; } ;
struct drm_device {struct mcde* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  component_master_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  mcde_drm_comp_ops ; 
 struct drm_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcde_remove(struct platform_device *pdev)
{
	struct drm_device *drm = platform_get_drvdata(pdev);
	struct mcde *mcde = drm->dev_private;

	component_master_del(&pdev->dev, &mcde_drm_comp_ops);
	clk_disable_unprepare(mcde->mcde_clk);
	regulator_disable(mcde->vana);
	regulator_disable(mcde->epod);
	drm_dev_put(drm);

	return 0;
}