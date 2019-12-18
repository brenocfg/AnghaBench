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
struct ingenic_drm {int /*<<< orphan*/  drm; scalar_t__ pix_clk; scalar_t__ lcd_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_unregister (int /*<<< orphan*/ *) ; 
 struct ingenic_drm* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ingenic_drm_remove(struct platform_device *pdev)
{
	struct ingenic_drm *priv = platform_get_drvdata(pdev);

	if (priv->lcd_clk)
		clk_disable_unprepare(priv->lcd_clk);
	clk_disable_unprepare(priv->pix_clk);

	drm_dev_unregister(&priv->drm);
	drm_atomic_helper_shutdown(&priv->drm);

	return 0;
}