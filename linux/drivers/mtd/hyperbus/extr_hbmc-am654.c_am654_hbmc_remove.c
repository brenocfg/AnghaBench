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
struct am654_hbmc_priv {scalar_t__ mux_ctrl; int /*<<< orphan*/  hbdev; } ;

/* Variables and functions */
 int hyperbus_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mux_control_deselect (scalar_t__) ; 
 struct am654_hbmc_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int am654_hbmc_remove(struct platform_device *pdev)
{
	struct am654_hbmc_priv *priv = platform_get_drvdata(pdev);
	int ret;

	ret = hyperbus_unregister_device(&priv->hbdev);
	if (priv->mux_ctrl)
		mux_control_deselect(priv->mux_ctrl);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	return ret;
}