#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct rockchip_usb_phy_base {int /*<<< orphan*/  dev; TYPE_2__* pdata; } ;
struct TYPE_17__ {struct clk_init_data* init; } ;
struct rockchip_usb_phy {unsigned int reg_offset; int uart_enabled; TYPE_3__* clk; TYPE_3__* clk480m; TYPE_3__* vbus; TYPE_3__* phy; TYPE_11__ clk480m_hw; TYPE_3__* reset; struct device_node* np; struct rockchip_usb_phy_base* base; } ;
struct device_node {int dummy; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; scalar_t__ flags; int /*<<< orphan*/ * name; } ;
struct TYPE_20__ {int /*<<< orphan*/  dev; } ;
struct TYPE_19__ {int usb_uart_phy; TYPE_1__* phys; } ;
struct TYPE_18__ {int reg; int /*<<< orphan*/ * pll_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int PTR_ERR (TYPE_3__*) ; 
 char* __clk_get_name (TYPE_3__*) ; 
 int clk_prepare_enable (TYPE_3__*) ; 
 int /*<<< orphan*/  clk_put (TYPE_3__*) ; 
 TYPE_3__* clk_register (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  clk_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int devm_add_action_or_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rockchip_usb_phy*) ; 
 struct rockchip_usb_phy* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* devm_phy_create (int /*<<< orphan*/ ,struct device_node*,int /*<<< orphan*/ *) ; 
 TYPE_3__* devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ enable_usb_uart ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_3__* of_clk_get_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned int*) ; 
 TYPE_3__* of_reset_control_get (struct device_node*,char*) ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (TYPE_3__*,struct rockchip_usb_phy*) ; 
 int /*<<< orphan*/  rockchip_usb_phy480m_ops ; 
 int /*<<< orphan*/  rockchip_usb_phy_action ; 
 int rockchip_usb_phy_power (struct rockchip_usb_phy*,int) ; 

__attribute__((used)) static int rockchip_usb_phy_init(struct rockchip_usb_phy_base *base,
				 struct device_node *child)
{
	struct rockchip_usb_phy *rk_phy;
	unsigned int reg_offset;
	const char *clk_name;
	struct clk_init_data init;
	int err, i;

	rk_phy = devm_kzalloc(base->dev, sizeof(*rk_phy), GFP_KERNEL);
	if (!rk_phy)
		return -ENOMEM;

	rk_phy->base = base;
	rk_phy->np = child;

	if (of_property_read_u32(child, "reg", &reg_offset)) {
		dev_err(base->dev, "missing reg property in node %pOFn\n",
			child);
		return -EINVAL;
	}

	rk_phy->reset = of_reset_control_get(child, "phy-reset");
	if (IS_ERR(rk_phy->reset))
		rk_phy->reset = NULL;

	rk_phy->reg_offset = reg_offset;

	rk_phy->clk = of_clk_get_by_name(child, "phyclk");
	if (IS_ERR(rk_phy->clk))
		rk_phy->clk = NULL;

	i = 0;
	init.name = NULL;
	while (base->pdata->phys[i].reg) {
		if (base->pdata->phys[i].reg == reg_offset) {
			init.name = base->pdata->phys[i].pll_name;
			break;
		}
		i++;
	}

	if (!init.name) {
		dev_err(base->dev, "phy data not found\n");
		return -EINVAL;
	}

	if (enable_usb_uart && base->pdata->usb_uart_phy == i) {
		dev_dbg(base->dev, "phy%d used as uart output\n", i);
		rk_phy->uart_enabled = true;
	} else {
		if (rk_phy->clk) {
			clk_name = __clk_get_name(rk_phy->clk);
			init.flags = 0;
			init.parent_names = &clk_name;
			init.num_parents = 1;
		} else {
			init.flags = 0;
			init.parent_names = NULL;
			init.num_parents = 0;
		}

		init.ops = &rockchip_usb_phy480m_ops;
		rk_phy->clk480m_hw.init = &init;

		rk_phy->clk480m = clk_register(base->dev, &rk_phy->clk480m_hw);
		if (IS_ERR(rk_phy->clk480m)) {
			err = PTR_ERR(rk_phy->clk480m);
			goto err_clk;
		}

		err = of_clk_add_provider(child, of_clk_src_simple_get,
					rk_phy->clk480m);
		if (err < 0)
			goto err_clk_prov;
	}

	err = devm_add_action_or_reset(base->dev, rockchip_usb_phy_action,
				       rk_phy);
	if (err)
		return err;

	rk_phy->phy = devm_phy_create(base->dev, child, &ops);
	if (IS_ERR(rk_phy->phy)) {
		dev_err(base->dev, "failed to create PHY\n");
		return PTR_ERR(rk_phy->phy);
	}
	phy_set_drvdata(rk_phy->phy, rk_phy);

	rk_phy->vbus = devm_regulator_get_optional(&rk_phy->phy->dev, "vbus");
	if (IS_ERR(rk_phy->vbus)) {
		if (PTR_ERR(rk_phy->vbus) == -EPROBE_DEFER)
			return PTR_ERR(rk_phy->vbus);
		rk_phy->vbus = NULL;
	}

	/*
	 * When acting as uart-pipe, just keep clock on otherwise
	 * only power up usb phy when it use, so disable it when init
	 */
	if (rk_phy->uart_enabled)
		return clk_prepare_enable(rk_phy->clk);
	else
		return rockchip_usb_phy_power(rk_phy, 1);

err_clk_prov:
	if (!rk_phy->uart_enabled)
		clk_unregister(rk_phy->clk480m);
err_clk:
	if (rk_phy->clk)
		clk_put(rk_phy->clk);
	return err;
}