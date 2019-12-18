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
struct dim2_hdm {scalar_t__ clk_speed; void* clk_pll; scalar_t__ io_base; void* clk; } ;

/* Variables and functions */
 scalar_t__ CLK_2048FS ; 
 int EFAULT ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct dim2_hdm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int fsl_mx6_enable(struct platform_device *pdev)
{
	struct dim2_hdm *dev = platform_get_drvdata(pdev);
	int ret;

	dev->clk = devm_clk_get(&pdev->dev, "mlb");
	if (IS_ERR_OR_NULL(dev->clk)) {
		dev_err(&pdev->dev, "unable to get mlb clock\n");
		return -EFAULT;
	}

	ret = clk_prepare_enable(dev->clk);
	if (ret) {
		dev_err(&pdev->dev, "%s\n", "clk_prepare_enable failed");
		return ret;
	}

	if (dev->clk_speed >= CLK_2048FS) {
		/* enable pll */
		dev->clk_pll = devm_clk_get(&pdev->dev, "pll8_mlb");
		if (IS_ERR_OR_NULL(dev->clk_pll)) {
			dev_err(&pdev->dev, "unable to get mlb pll clock\n");
			clk_disable_unprepare(dev->clk);
			return -EFAULT;
		}

		writel(0x888, dev->io_base + 0x38);
		clk_prepare_enable(dev->clk_pll);
	}

	return 0;
}