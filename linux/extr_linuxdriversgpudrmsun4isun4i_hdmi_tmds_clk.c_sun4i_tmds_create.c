#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct clk_init_data* init; } ;
struct sun4i_tmds {TYPE_2__ hw; int /*<<< orphan*/  div_offset; struct sun4i_hdmi* hdmi; } ;
struct sun4i_hdmi {int /*<<< orphan*/  tmds_clk; int /*<<< orphan*/  dev; TYPE_1__* variant; int /*<<< orphan*/  pll1_clk; int /*<<< orphan*/  pll0_clk; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  tmds_clk_div_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 char* __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct sun4i_tmds* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_tmds_ops ; 

int sun4i_tmds_create(struct sun4i_hdmi *hdmi)
{
	struct clk_init_data init;
	struct sun4i_tmds *tmds;
	const char *parents[2];

	parents[0] = __clk_get_name(hdmi->pll0_clk);
	if (!parents[0])
		return -ENODEV;

	parents[1] = __clk_get_name(hdmi->pll1_clk);
	if (!parents[1])
		return -ENODEV;

	tmds = devm_kzalloc(hdmi->dev, sizeof(*tmds), GFP_KERNEL);
	if (!tmds)
		return -ENOMEM;

	init.name = "hdmi-tmds";
	init.ops = &sun4i_tmds_ops;
	init.parent_names = parents;
	init.num_parents = 2;
	init.flags = CLK_SET_RATE_PARENT;

	tmds->hdmi = hdmi;
	tmds->hw.init = &init;
	tmds->div_offset = hdmi->variant->tmds_clk_div_offset;

	hdmi->tmds_clk = devm_clk_register(hdmi->dev, &tmds->hw);
	if (IS_ERR(hdmi->tmds_clk))
		return PTR_ERR(hdmi->tmds_clk);

	return 0;
}