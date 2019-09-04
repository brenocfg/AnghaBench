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
struct rockchip_rga {int /*<<< orphan*/  aclk; int /*<<< orphan*/  sclk; int /*<<< orphan*/  dev; int /*<<< orphan*/  hclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rga_enable_clocks(struct rockchip_rga *rga)
{
	int ret;

	ret = clk_prepare_enable(rga->sclk);
	if (ret) {
		dev_err(rga->dev, "Cannot enable rga sclk: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(rga->aclk);
	if (ret) {
		dev_err(rga->dev, "Cannot enable rga aclk: %d\n", ret);
		goto err_disable_sclk;
	}

	ret = clk_prepare_enable(rga->hclk);
	if (ret) {
		dev_err(rga->dev, "Cannot enable rga hclk: %d\n", ret);
		goto err_disable_aclk;
	}

	return 0;

err_disable_sclk:
	clk_disable_unprepare(rga->sclk);
err_disable_aclk:
	clk_disable_unprepare(rga->aclk);

	return ret;
}