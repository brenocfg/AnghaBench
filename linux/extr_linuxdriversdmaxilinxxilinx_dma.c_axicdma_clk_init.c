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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int axicdma_clk_init(struct platform_device *pdev, struct clk **axi_clk,
			    struct clk **dev_clk, struct clk **tmp_clk,
			    struct clk **tmp1_clk, struct clk **tmp2_clk)
{
	int err;

	*tmp_clk = NULL;
	*tmp1_clk = NULL;
	*tmp2_clk = NULL;

	*axi_clk = devm_clk_get(&pdev->dev, "s_axi_lite_aclk");
	if (IS_ERR(*axi_clk)) {
		err = PTR_ERR(*axi_clk);
		dev_err(&pdev->dev, "failed to get axi_clk (%d)\n", err);
		return err;
	}

	*dev_clk = devm_clk_get(&pdev->dev, "m_axi_aclk");
	if (IS_ERR(*dev_clk)) {
		err = PTR_ERR(*dev_clk);
		dev_err(&pdev->dev, "failed to get dev_clk (%d)\n", err);
		return err;
	}

	err = clk_prepare_enable(*axi_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)\n", err);
		return err;
	}

	err = clk_prepare_enable(*dev_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable dev_clk (%d)\n", err);
		goto err_disable_axiclk;
	}

	return 0;

err_disable_axiclk:
	clk_disable_unprepare(*axi_clk);

	return err;
}