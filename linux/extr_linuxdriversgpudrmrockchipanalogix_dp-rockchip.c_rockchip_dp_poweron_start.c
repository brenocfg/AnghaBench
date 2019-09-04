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
struct rockchip_dp_device {int /*<<< orphan*/  pclk; int /*<<< orphan*/  dev; } ;
struct analogix_dp_plat_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int rockchip_dp_pre_init (struct rockchip_dp_device*) ; 
 struct rockchip_dp_device* to_dp (struct analogix_dp_plat_data*) ; 

__attribute__((used)) static int rockchip_dp_poweron_start(struct analogix_dp_plat_data *plat_data)
{
	struct rockchip_dp_device *dp = to_dp(plat_data);
	int ret;

	ret = clk_prepare_enable(dp->pclk);
	if (ret < 0) {
		DRM_DEV_ERROR(dp->dev, "failed to enable pclk %d\n", ret);
		return ret;
	}

	ret = rockchip_dp_pre_init(dp);
	if (ret < 0) {
		DRM_DEV_ERROR(dp->dev, "failed to dp pre init %d\n", ret);
		clk_disable_unprepare(dp->pclk);
		return ret;
	}

	return ret;
}