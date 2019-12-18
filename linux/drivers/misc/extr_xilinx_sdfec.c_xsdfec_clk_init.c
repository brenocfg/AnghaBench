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
struct xsdfec_clks {int /*<<< orphan*/ * core_clk; int /*<<< orphan*/ * axi_clk; int /*<<< orphan*/ * din_clk; int /*<<< orphan*/ * din_words_clk; int /*<<< orphan*/ * dout_clk; int /*<<< orphan*/ * dout_words_clk; int /*<<< orphan*/ * ctrl_clk; int /*<<< orphan*/ * status_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int xsdfec_clk_init(struct platform_device *pdev,
			   struct xsdfec_clks *clks)
{
	int err;

	clks->core_clk = devm_clk_get(&pdev->dev, "core_clk");
	if (IS_ERR(clks->core_clk)) {
		dev_err(&pdev->dev, "failed to get core_clk");
		return PTR_ERR(clks->core_clk);
	}

	clks->axi_clk = devm_clk_get(&pdev->dev, "s_axi_aclk");
	if (IS_ERR(clks->axi_clk)) {
		dev_err(&pdev->dev, "failed to get axi_clk");
		return PTR_ERR(clks->axi_clk);
	}

	clks->din_words_clk = devm_clk_get(&pdev->dev, "s_axis_din_words_aclk");
	if (IS_ERR(clks->din_words_clk)) {
		if (PTR_ERR(clks->din_words_clk) != -ENOENT) {
			err = PTR_ERR(clks->din_words_clk);
			return err;
		}
		clks->din_words_clk = NULL;
	}

	clks->din_clk = devm_clk_get(&pdev->dev, "s_axis_din_aclk");
	if (IS_ERR(clks->din_clk)) {
		if (PTR_ERR(clks->din_clk) != -ENOENT) {
			err = PTR_ERR(clks->din_clk);
			return err;
		}
		clks->din_clk = NULL;
	}

	clks->dout_clk = devm_clk_get(&pdev->dev, "m_axis_dout_aclk");
	if (IS_ERR(clks->dout_clk)) {
		if (PTR_ERR(clks->dout_clk) != -ENOENT) {
			err = PTR_ERR(clks->dout_clk);
			return err;
		}
		clks->dout_clk = NULL;
	}

	clks->dout_words_clk =
		devm_clk_get(&pdev->dev, "s_axis_dout_words_aclk");
	if (IS_ERR(clks->dout_words_clk)) {
		if (PTR_ERR(clks->dout_words_clk) != -ENOENT) {
			err = PTR_ERR(clks->dout_words_clk);
			return err;
		}
		clks->dout_words_clk = NULL;
	}

	clks->ctrl_clk = devm_clk_get(&pdev->dev, "s_axis_ctrl_aclk");
	if (IS_ERR(clks->ctrl_clk)) {
		if (PTR_ERR(clks->ctrl_clk) != -ENOENT) {
			err = PTR_ERR(clks->ctrl_clk);
			return err;
		}
		clks->ctrl_clk = NULL;
	}

	clks->status_clk = devm_clk_get(&pdev->dev, "m_axis_status_aclk");
	if (IS_ERR(clks->status_clk)) {
		if (PTR_ERR(clks->status_clk) != -ENOENT) {
			err = PTR_ERR(clks->status_clk);
			return err;
		}
		clks->status_clk = NULL;
	}

	err = clk_prepare_enable(clks->core_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable core_clk (%d)", err);
		return err;
	}

	err = clk_prepare_enable(clks->axi_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)", err);
		goto err_disable_core_clk;
	}

	err = clk_prepare_enable(clks->din_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable din_clk (%d)", err);
		goto err_disable_axi_clk;
	}

	err = clk_prepare_enable(clks->din_words_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable din_words_clk (%d)", err);
		goto err_disable_din_clk;
	}

	err = clk_prepare_enable(clks->dout_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable dout_clk (%d)", err);
		goto err_disable_din_words_clk;
	}

	err = clk_prepare_enable(clks->dout_words_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable dout_words_clk (%d)",
			err);
		goto err_disable_dout_clk;
	}

	err = clk_prepare_enable(clks->ctrl_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable ctrl_clk (%d)", err);
		goto err_disable_dout_words_clk;
	}

	err = clk_prepare_enable(clks->status_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable status_clk (%d)\n", err);
		goto err_disable_ctrl_clk;
	}

	return err;

err_disable_ctrl_clk:
	clk_disable_unprepare(clks->ctrl_clk);
err_disable_dout_words_clk:
	clk_disable_unprepare(clks->dout_words_clk);
err_disable_dout_clk:
	clk_disable_unprepare(clks->dout_clk);
err_disable_din_words_clk:
	clk_disable_unprepare(clks->din_words_clk);
err_disable_din_clk:
	clk_disable_unprepare(clks->din_clk);
err_disable_axi_clk:
	clk_disable_unprepare(clks->axi_clk);
err_disable_core_clk:
	clk_disable_unprepare(clks->core_clk);

	return err;
}