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
struct emac_adapter {struct clk** clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 unsigned int EMAC_CLK_CNT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 struct clk* devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * emac_clk_name ; 

__attribute__((used)) static int emac_clks_get(struct platform_device *pdev,
			 struct emac_adapter *adpt)
{
	unsigned int i;

	for (i = 0; i < EMAC_CLK_CNT; i++) {
		struct clk *clk = devm_clk_get(&pdev->dev, emac_clk_name[i]);

		if (IS_ERR(clk)) {
			dev_err(&pdev->dev,
				"could not claim clock %s (error=%li)\n",
				emac_clk_name[i], PTR_ERR(clk));

			return PTR_ERR(clk);
		}

		adpt->clk[i] = clk;
	}

	return 0;
}