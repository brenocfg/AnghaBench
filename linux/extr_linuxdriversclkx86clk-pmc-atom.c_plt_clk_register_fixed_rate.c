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
struct clk_plt_fixed {int /*<<< orphan*/  clk; int /*<<< orphan*/  lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk_plt_fixed* ERR_CAST (int /*<<< orphan*/ ) ; 
 struct clk_plt_fixed* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_register_fixed_rate (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdev_hw_create (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 struct clk_plt_fixed* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_plt_fixed *plt_clk_register_fixed_rate(struct platform_device *pdev,
						 const char *name,
						 const char *parent_name,
						 unsigned long fixed_rate)
{
	struct clk_plt_fixed *pclk;

	pclk = devm_kzalloc(&pdev->dev, sizeof(*pclk), GFP_KERNEL);
	if (!pclk)
		return ERR_PTR(-ENOMEM);

	pclk->clk = clk_hw_register_fixed_rate(&pdev->dev, name, parent_name,
					       0, fixed_rate);
	if (IS_ERR(pclk->clk))
		return ERR_CAST(pclk->clk);

	pclk->lookup = clkdev_hw_create(pclk->clk, name, NULL);
	if (!pclk->lookup) {
		clk_hw_unregister_fixed_rate(pclk->clk);
		return ERR_PTR(-ENOMEM);
	}

	return pclk;
}