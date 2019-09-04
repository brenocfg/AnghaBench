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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct clk_onecell_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_APMIXED_NR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  apmixed_fixed_divs ; 
 int /*<<< orphan*/  apmixed_plls ; 
 struct clk_onecell_data* mtk_alloc_clk_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_clk_register_factors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  mtk_clk_register_plls (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct clk_onecell_data*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 

__attribute__((used)) static int mtk_apmixedsys_init(struct platform_device *pdev)
{
	struct clk_onecell_data *clk_data;
	struct device_node *node = pdev->dev.of_node;

	clk_data = mtk_alloc_clk_data(CLK_APMIXED_NR);
	if (!clk_data)
		return -ENOMEM;

	mtk_clk_register_plls(node, apmixed_plls, ARRAY_SIZE(apmixed_plls),
								clk_data);
	mtk_clk_register_factors(apmixed_fixed_divs, ARRAY_SIZE(apmixed_fixed_divs),
								clk_data);

	return of_clk_add_provider(node, of_clk_src_onecell_get, clk_data);
}