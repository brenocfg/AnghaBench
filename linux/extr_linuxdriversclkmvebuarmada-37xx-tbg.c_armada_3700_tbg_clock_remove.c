#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk_hw_onecell_data {int num; int /*<<< orphan*/ * hws; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister_fixed_factor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct clk_hw_onecell_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int armada_3700_tbg_clock_remove(struct platform_device *pdev)
{
	int i;
	struct clk_hw_onecell_data *hw_tbg_data = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	for (i = 0; i < hw_tbg_data->num; i++)
		clk_hw_unregister_fixed_factor(hw_tbg_data->hws[i]);

	return 0;
}