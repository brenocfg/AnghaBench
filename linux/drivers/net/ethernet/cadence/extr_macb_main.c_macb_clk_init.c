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
struct macb_platform_data {struct clk* hclk; struct clk* pclk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct macb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct clk* devm_clk_get_optional (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int macb_clk_init(struct platform_device *pdev, struct clk **pclk,
			 struct clk **hclk, struct clk **tx_clk,
			 struct clk **rx_clk, struct clk **tsu_clk)
{
	struct macb_platform_data *pdata;
	int err;

	pdata = dev_get_platdata(&pdev->dev);
	if (pdata) {
		*pclk = pdata->pclk;
		*hclk = pdata->hclk;
	} else {
		*pclk = devm_clk_get(&pdev->dev, "pclk");
		*hclk = devm_clk_get(&pdev->dev, "hclk");
	}

	if (IS_ERR_OR_NULL(*pclk)) {
		err = PTR_ERR(*pclk);
		if (!err)
			err = -ENODEV;

		dev_err(&pdev->dev, "failed to get macb_clk (%d)\n", err);
		return err;
	}

	if (IS_ERR_OR_NULL(*hclk)) {
		err = PTR_ERR(*hclk);
		if (!err)
			err = -ENODEV;

		dev_err(&pdev->dev, "failed to get hclk (%d)\n", err);
		return err;
	}

	*tx_clk = devm_clk_get_optional(&pdev->dev, "tx_clk");
	if (IS_ERR(*tx_clk))
		return PTR_ERR(*tx_clk);

	*rx_clk = devm_clk_get_optional(&pdev->dev, "rx_clk");
	if (IS_ERR(*rx_clk))
		return PTR_ERR(*rx_clk);

	*tsu_clk = devm_clk_get_optional(&pdev->dev, "tsu_clk");
	if (IS_ERR(*tsu_clk))
		return PTR_ERR(*tsu_clk);

	err = clk_prepare_enable(*pclk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable pclk (%d)\n", err);
		return err;
	}

	err = clk_prepare_enable(*hclk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable hclk (%d)\n", err);
		goto err_disable_pclk;
	}

	err = clk_prepare_enable(*tx_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable tx_clk (%d)\n", err);
		goto err_disable_hclk;
	}

	err = clk_prepare_enable(*rx_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable rx_clk (%d)\n", err);
		goto err_disable_txclk;
	}

	err = clk_prepare_enable(*tsu_clk);
	if (err) {
		dev_err(&pdev->dev, "failed to enable tsu_clk (%d)\n", err);
		goto err_disable_rxclk;
	}

	return 0;

err_disable_rxclk:
	clk_disable_unprepare(*rx_clk);

err_disable_txclk:
	clk_disable_unprepare(*tx_clk);

err_disable_hclk:
	clk_disable_unprepare(*hclk);

err_disable_pclk:
	clk_disable_unprepare(*pclk);

	return err;
}