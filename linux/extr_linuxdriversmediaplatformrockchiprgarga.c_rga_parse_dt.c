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
struct rockchip_rga {struct reset_control* hclk; int /*<<< orphan*/  dev; struct reset_control* aclk; struct reset_control* sclk; } ;
struct reset_control {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 
 struct reset_control* devm_reset_control_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rga_parse_dt(struct rockchip_rga *rga)
{
	struct reset_control *core_rst, *axi_rst, *ahb_rst;

	core_rst = devm_reset_control_get(rga->dev, "core");
	if (IS_ERR(core_rst)) {
		dev_err(rga->dev, "failed to get core reset controller\n");
		return PTR_ERR(core_rst);
	}

	axi_rst = devm_reset_control_get(rga->dev, "axi");
	if (IS_ERR(axi_rst)) {
		dev_err(rga->dev, "failed to get axi reset controller\n");
		return PTR_ERR(axi_rst);
	}

	ahb_rst = devm_reset_control_get(rga->dev, "ahb");
	if (IS_ERR(ahb_rst)) {
		dev_err(rga->dev, "failed to get ahb reset controller\n");
		return PTR_ERR(ahb_rst);
	}

	reset_control_assert(core_rst);
	udelay(1);
	reset_control_deassert(core_rst);

	reset_control_assert(axi_rst);
	udelay(1);
	reset_control_deassert(axi_rst);

	reset_control_assert(ahb_rst);
	udelay(1);
	reset_control_deassert(ahb_rst);

	rga->sclk = devm_clk_get(rga->dev, "sclk");
	if (IS_ERR(rga->sclk)) {
		dev_err(rga->dev, "failed to get sclk clock\n");
		return PTR_ERR(rga->sclk);
	}

	rga->aclk = devm_clk_get(rga->dev, "aclk");
	if (IS_ERR(rga->aclk)) {
		dev_err(rga->dev, "failed to get aclk clock\n");
		return PTR_ERR(rga->aclk);
	}

	rga->hclk = devm_clk_get(rga->dev, "hclk");
	if (IS_ERR(rga->hclk)) {
		dev_err(rga->dev, "failed to get hclk clock\n");
		return PTR_ERR(rga->hclk);
	}

	return 0;
}