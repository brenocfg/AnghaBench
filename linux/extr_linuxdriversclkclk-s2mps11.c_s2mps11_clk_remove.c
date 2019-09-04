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
struct s2mps11_clk {int /*<<< orphan*/  lookup; int /*<<< orphan*/  clk_np; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int S2MPS11_CLKS_NUM ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct s2mps11_clk* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int s2mps11_clk_remove(struct platform_device *pdev)
{
	struct s2mps11_clk *s2mps11_clks = platform_get_drvdata(pdev);
	int i;

	of_clk_del_provider(s2mps11_clks[0].clk_np);
	/* Drop the reference obtained in s2mps11_clk_parse_dt */
	of_node_put(s2mps11_clks[0].clk_np);

	for (i = 0; i < S2MPS11_CLKS_NUM; i++) {
		/* Skip clocks not present on S2MPS14 */
		if (!s2mps11_clks[i].lookup)
			continue;
		clkdev_drop(s2mps11_clks[i].lookup);
	}

	return 0;
}