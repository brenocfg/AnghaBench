#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct isc_device {TYPE_1__* dev; struct isc_clk* isc_clks; struct regmap* regmap; } ;
struct TYPE_5__ {struct clk_init_data* init; } ;
struct isc_clk {unsigned int id; int /*<<< orphan*/  clk; TYPE_3__ hw; int /*<<< orphan*/  lock; TYPE_1__* dev; struct regmap* regmap; } ;
struct device_node {char* name; } ;
struct clk_init_data {char const** parent_names; int num_parents; char const* name; int flags; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int CLK_SET_PARENT_GATE ; 
 int CLK_SET_RATE_GATE ; 
 int EINVAL ; 
 unsigned int ISC_ISPCK ; 
 unsigned int ISC_MCK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_register (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  isc_clk_ops ; 
 int /*<<< orphan*/  of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_clk_get_parent_count (struct device_node*) ; 
 int /*<<< orphan*/  of_clk_parent_fill (struct device_node*,char const**,int) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isc_clk_register(struct isc_device *isc, unsigned int id)
{
	struct regmap *regmap = isc->regmap;
	struct device_node *np = isc->dev->of_node;
	struct isc_clk *isc_clk;
	struct clk_init_data init;
	const char *clk_name = np->name;
	const char *parent_names[3];
	int num_parents;

	num_parents = of_clk_get_parent_count(np);
	if (num_parents < 1 || num_parents > 3)
		return -EINVAL;

	if (num_parents > 2 && id == ISC_ISPCK)
		num_parents = 2;

	of_clk_parent_fill(np, parent_names, num_parents);

	if (id == ISC_MCK)
		of_property_read_string(np, "clock-output-names", &clk_name);
	else
		clk_name = "isc-ispck";

	init.parent_names	= parent_names;
	init.num_parents	= num_parents;
	init.name		= clk_name;
	init.ops		= &isc_clk_ops;
	init.flags		= CLK_SET_RATE_GATE | CLK_SET_PARENT_GATE;

	isc_clk = &isc->isc_clks[id];
	isc_clk->hw.init	= &init;
	isc_clk->regmap		= regmap;
	isc_clk->id		= id;
	isc_clk->dev		= isc->dev;
	spin_lock_init(&isc_clk->lock);

	isc_clk->clk = clk_register(isc->dev, &isc_clk->hw);
	if (IS_ERR(isc_clk->clk)) {
		dev_err(isc->dev, "%s: clock register fail\n", clk_name);
		return PTR_ERR(isc_clk->clk);
	} else if (id == ISC_MCK)
		of_clk_add_provider(np, of_clk_src_simple_get, isc_clk->clk);

	return 0;
}