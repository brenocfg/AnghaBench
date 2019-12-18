#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ci_hdrc_imx_data {scalar_t__ hsic_pad_regulator; int /*<<< orphan*/  pm_qos_req; TYPE_1__* plat_data; scalar_t__ ci_pdev; int /*<<< orphan*/  phy; scalar_t__ override_phy_control; scalar_t__ supports_runtime_pm; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CI_HDRC_PMQOS ; 
 int /*<<< orphan*/  ci_hdrc_remove_device (scalar_t__) ; 
 int /*<<< orphan*/  imx_disable_unprepare_clks (int /*<<< orphan*/ *) ; 
 struct ci_hdrc_imx_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int /*<<< orphan*/  usb_phy_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ci_hdrc_imx_remove(struct platform_device *pdev)
{
	struct ci_hdrc_imx_data *data = platform_get_drvdata(pdev);

	if (data->supports_runtime_pm) {
		pm_runtime_get_sync(&pdev->dev);
		pm_runtime_disable(&pdev->dev);
		pm_runtime_put_noidle(&pdev->dev);
	}
	if (data->ci_pdev)
		ci_hdrc_remove_device(data->ci_pdev);
	if (data->override_phy_control)
		usb_phy_shutdown(data->phy);
	if (data->ci_pdev) {
		imx_disable_unprepare_clks(&pdev->dev);
		if (data->plat_data->flags & CI_HDRC_PMQOS)
			pm_qos_remove_request(&data->pm_qos_req);
		if (data->hsic_pad_regulator)
			regulator_disable(data->hsic_pad_regulator);
	}

	return 0;
}