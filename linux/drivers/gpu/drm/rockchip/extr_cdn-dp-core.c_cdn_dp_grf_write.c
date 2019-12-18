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
struct cdn_dp_device {int /*<<< orphan*/  grf_clk; int /*<<< orphan*/  dev; int /*<<< orphan*/  grf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int cdn_dp_grf_write(struct cdn_dp_device *dp,
			    unsigned int reg, unsigned int val)
{
	int ret;

	ret = clk_prepare_enable(dp->grf_clk);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to prepare_enable grf clock\n");
		return ret;
	}

	ret = regmap_write(dp->grf, reg, val);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Could not write to GRF: %d\n", ret);
		return ret;
	}

	clk_disable_unprepare(dp->grf_clk);

	return 0;
}