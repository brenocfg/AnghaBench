#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msm_dsi_host {int power_on; int /*<<< orphan*/  dev_mutex; TYPE_2__* pdev; scalar_t__ disp_en_gpio; struct msm_dsi_cfg_handler* cfg_hnd; } ;
struct msm_dsi_cfg_handler {TYPE_1__* ops; } ;
struct mipi_dsi_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* link_clk_disable ) (struct msm_dsi_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  dsi_ctrl_config (struct msm_dsi_host*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsi_host_regulator_disable (struct msm_dsi_host*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_dsi_sfpb_config (struct msm_dsi_host*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct msm_dsi_host*) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

int msm_dsi_host_power_off(struct mipi_dsi_host *host)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const struct msm_dsi_cfg_handler *cfg_hnd = msm_host->cfg_hnd;

	mutex_lock(&msm_host->dev_mutex);
	if (!msm_host->power_on) {
		DBG("dsi host already off");
		goto unlock_ret;
	}

	dsi_ctrl_config(msm_host, false, NULL);

	if (msm_host->disp_en_gpio)
		gpiod_set_value(msm_host->disp_en_gpio, 0);

	pinctrl_pm_select_sleep_state(&msm_host->pdev->dev);

	cfg_hnd->ops->link_clk_disable(msm_host);
	pm_runtime_put_autosuspend(&msm_host->pdev->dev);

	dsi_host_regulator_disable(msm_host);

	msm_dsi_sfpb_config(msm_host, false);

	DBG("-");

	msm_host->power_on = false;

unlock_ret:
	mutex_unlock(&msm_host->dev_mutex);
	return 0;
}