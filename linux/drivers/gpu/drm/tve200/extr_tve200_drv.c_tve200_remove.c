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
struct tve200_drm_dev_private {int /*<<< orphan*/  pclk; int /*<<< orphan*/  bridge; scalar_t__ panel; } ;
struct platform_device {int dummy; } ;
struct drm_device {struct tve200_drm_dev_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_panel_bridge_remove (int /*<<< orphan*/ ) ; 
 struct drm_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int tve200_remove(struct platform_device *pdev)
{
	struct drm_device *drm = platform_get_drvdata(pdev);
	struct tve200_drm_dev_private *priv = drm->dev_private;

	drm_dev_unregister(drm);
	if (priv->panel)
		drm_panel_bridge_remove(priv->bridge);
	drm_mode_config_cleanup(drm);
	clk_disable_unprepare(priv->pclk);
	drm_dev_put(drm);

	return 0;
}