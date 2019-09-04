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
struct sun4i_hdmi {int /*<<< orphan*/  ddc_clk; int /*<<< orphan*/  dev; TYPE_1__* variant; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {struct clk_init_data* init; } ;
struct sun4i_ddc {TYPE_2__ hw; int /*<<< orphan*/  m_offset; int /*<<< orphan*/  pre_div; struct sun4i_hdmi* hdmi; int /*<<< orphan*/  reg; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ddc_clk_m_offset; int /*<<< orphan*/  ddc_clk_pre_divider; int /*<<< orphan*/  ddc_clk_reg; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 char* __clk_get_name (struct clk*) ; 
 int /*<<< orphan*/  devm_clk_register (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct sun4i_ddc* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun4i_ddc_ops ; 

int sun4i_ddc_create(struct sun4i_hdmi *hdmi, struct clk *parent)
{
	struct clk_init_data init;
	struct sun4i_ddc *ddc;
	const char *parent_name;

	parent_name = __clk_get_name(parent);
	if (!parent_name)
		return -ENODEV;

	ddc = devm_kzalloc(hdmi->dev, sizeof(*ddc), GFP_KERNEL);
	if (!ddc)
		return -ENOMEM;

	ddc->reg = devm_regmap_field_alloc(hdmi->dev, hdmi->regmap,
					   hdmi->variant->ddc_clk_reg);
	if (IS_ERR(ddc->reg))
		return PTR_ERR(ddc->reg);

	init.name = "hdmi-ddc";
	init.ops = &sun4i_ddc_ops;
	init.parent_names = &parent_name;
	init.num_parents = 1;

	ddc->hdmi = hdmi;
	ddc->hw.init = &init;
	ddc->pre_div = hdmi->variant->ddc_clk_pre_divider;
	ddc->m_offset = hdmi->variant->ddc_clk_m_offset;

	hdmi->ddc_clk = devm_clk_register(hdmi->dev, &ddc->hw);
	if (IS_ERR(hdmi->ddc_clk))
		return PTR_ERR(hdmi->ddc_clk);

	return 0;
}