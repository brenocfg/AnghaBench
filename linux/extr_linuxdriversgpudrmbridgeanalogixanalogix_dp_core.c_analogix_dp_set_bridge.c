#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct analogix_dp_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  clock; TYPE_1__* plat_data; int /*<<< orphan*/  phy; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_off ) (TYPE_1__*) ;int /*<<< orphan*/  (* power_on_end ) (TYPE_1__*) ;int /*<<< orphan*/  (* power_on_start ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int analogix_dp_commit (struct analogix_dp_device*) ; 
 int analogix_dp_detect_hpd (struct analogix_dp_device*) ; 
 int analogix_dp_init_dp (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

__attribute__((used)) static int analogix_dp_set_bridge(struct analogix_dp_device *dp)
{
	int ret;

	pm_runtime_get_sync(dp->dev);

	ret = clk_prepare_enable(dp->clock);
	if (ret < 0) {
		DRM_ERROR("Failed to prepare_enable the clock clk [%d]\n", ret);
		goto out_dp_clk_pre;
	}

	if (dp->plat_data->power_on_start)
		dp->plat_data->power_on_start(dp->plat_data);

	phy_power_on(dp->phy);

	ret = analogix_dp_init_dp(dp);
	if (ret)
		goto out_dp_init;

	/*
	 * According to DP spec v1.3 chap 3.5.1.2 Link Training,
	 * We should first make sure the HPD signal is asserted high by device
	 * when we want to establish a link with it.
	 */
	ret = analogix_dp_detect_hpd(dp);
	if (ret) {
		DRM_ERROR("failed to get hpd single ret = %d\n", ret);
		goto out_dp_init;
	}

	ret = analogix_dp_commit(dp);
	if (ret) {
		DRM_ERROR("dp commit error, ret = %d\n", ret);
		goto out_dp_init;
	}

	if (dp->plat_data->power_on_end)
		dp->plat_data->power_on_end(dp->plat_data);

	enable_irq(dp->irq);
	return 0;

out_dp_init:
	phy_power_off(dp->phy);
	if (dp->plat_data->power_off)
		dp->plat_data->power_off(dp->plat_data);
	clk_disable_unprepare(dp->clock);
out_dp_clk_pre:
	pm_runtime_put_sync(dp->dev);

	return ret;
}