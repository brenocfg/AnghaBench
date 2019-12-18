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
struct sun8i_tcon_top {int /*<<< orphan*/  rst; int /*<<< orphan*/  bus; struct clk_hw_onecell_data* clk_data; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct clk_hw_onecell_data {scalar_t__* hws; } ;

/* Variables and functions */
 int CLK_NUM ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_gate (scalar_t__) ; 
 struct sun8i_tcon_top* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun8i_tcon_top_unbind(struct device *dev, struct device *master,
				  void *data)
{
	struct sun8i_tcon_top *tcon_top = dev_get_drvdata(dev);
	struct clk_hw_onecell_data *clk_data = tcon_top->clk_data;
	int i;

	of_clk_del_provider(dev->of_node);
	for (i = 0; i < CLK_NUM; i++)
		if (clk_data->hws[i])
			clk_hw_unregister_gate(clk_data->hws[i]);

	clk_disable_unprepare(tcon_top->bus);
	reset_control_assert(tcon_top->rst);
}