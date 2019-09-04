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
typedef  int /*<<< orphan*/  u32 ;
struct sata_gemini {int sata_bridge; void* sata1_pclk; void* sata0_pclk; scalar_t__ base; void* sata1_reset; void* sata0_reset; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ GEMINI_SATA_ID ; 
 scalar_t__ GEMINI_SATA_PHY_ID ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  clk_disable (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (struct device*,char*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int gemini_sata_bridge_init(struct sata_gemini *sg)
{
	struct device *dev = sg->dev;
	u32 sata_id, sata_phy_id;
	int ret;

	sg->sata0_pclk = devm_clk_get(dev, "SATA0_PCLK");
	if (IS_ERR(sg->sata0_pclk)) {
		dev_err(dev, "no SATA0 PCLK");
		return -ENODEV;
	}
	sg->sata1_pclk = devm_clk_get(dev, "SATA1_PCLK");
	if (IS_ERR(sg->sata1_pclk)) {
		dev_err(dev, "no SATA1 PCLK");
		return -ENODEV;
	}

	ret = clk_prepare_enable(sg->sata0_pclk);
	if (ret) {
		pr_err("failed to enable SATA0 PCLK\n");
		return ret;
	}
	ret = clk_prepare_enable(sg->sata1_pclk);
	if (ret) {
		pr_err("failed to enable SATA1 PCLK\n");
		clk_disable_unprepare(sg->sata0_pclk);
		return ret;
	}

	sg->sata0_reset = devm_reset_control_get_exclusive(dev, "sata0");
	if (IS_ERR(sg->sata0_reset)) {
		dev_err(dev, "no SATA0 reset controller\n");
		clk_disable_unprepare(sg->sata1_pclk);
		clk_disable_unprepare(sg->sata0_pclk);
		return PTR_ERR(sg->sata0_reset);
	}
	sg->sata1_reset = devm_reset_control_get_exclusive(dev, "sata1");
	if (IS_ERR(sg->sata1_reset)) {
		dev_err(dev, "no SATA1 reset controller\n");
		clk_disable_unprepare(sg->sata1_pclk);
		clk_disable_unprepare(sg->sata0_pclk);
		return PTR_ERR(sg->sata1_reset);
	}

	sata_id = readl(sg->base + GEMINI_SATA_ID);
	sata_phy_id = readl(sg->base + GEMINI_SATA_PHY_ID);
	sg->sata_bridge = true;
	clk_disable(sg->sata0_pclk);
	clk_disable(sg->sata1_pclk);

	dev_info(dev, "SATA ID %08x, PHY ID: %08x\n", sata_id, sata_phy_id);

	return 0;
}