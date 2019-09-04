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
typedef  int u32 ;
struct spmi_pmic_div_clk_cc {int nclks; struct clkdiv* clks; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct clkdiv {int base; int cxo_period_ns; TYPE_1__ hw; struct regmap* regmap; int /*<<< orphan*/  lock; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int NSEC_PER_SEC ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_get (struct device*,char*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_spmi_pmic_div_ops ; 
 int /*<<< orphan*/  clks ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct regmap* dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_clk_hw_register (struct device*,TYPE_1__*) ; 
 struct spmi_pmic_div_clk_cc* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,struct spmi_pmic_div_clk_cc*) ; 
 char* of_clk_get_parent_name (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spmi_pmic_div_clk_hw_get ; 
 int /*<<< orphan*/  struct_size (struct spmi_pmic_div_clk_cc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int spmi_pmic_clkdiv_probe(struct platform_device *pdev)
{
	struct spmi_pmic_div_clk_cc *cc;
	struct clk_init_data init = {};
	struct clkdiv *clkdiv;
	struct clk *cxo;
	struct regmap *regmap;
	struct device *dev = &pdev->dev;
	struct device_node *of_node = dev->of_node;
	const char *parent_name;
	int nclks, i, ret, cxo_hz;
	char name[20];
	u32 start;

	ret = of_property_read_u32(of_node, "reg", &start);
	if (ret < 0) {
		dev_err(dev, "reg property reading failed\n");
		return ret;
	}

	regmap = dev_get_regmap(dev->parent, NULL);
	if (!regmap) {
		dev_err(dev, "Couldn't get parent's regmap\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(of_node, "qcom,num-clkdivs", &nclks);
	if (ret < 0) {
		dev_err(dev, "qcom,num-clkdivs property reading failed, ret=%d\n",
			ret);
		return ret;
	}

	if (!nclks)
		return -EINVAL;

	cc = devm_kzalloc(dev, struct_size(cc, clks, nclks), GFP_KERNEL);
	if (!cc)
		return -ENOMEM;
	cc->nclks = nclks;

	cxo = clk_get(dev, "xo");
	if (IS_ERR(cxo)) {
		ret = PTR_ERR(cxo);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get xo clock\n");
		return ret;
	}
	cxo_hz = clk_get_rate(cxo);
	clk_put(cxo);

	parent_name = of_clk_get_parent_name(of_node, 0);
	if (!parent_name) {
		dev_err(dev, "missing parent clock\n");
		return -ENODEV;
	}

	init.name = name;
	init.parent_names = &parent_name;
	init.num_parents = 1;
	init.ops = &clk_spmi_pmic_div_ops;

	for (i = 0, clkdiv = cc->clks; i < nclks; i++) {
		snprintf(name, sizeof(name), "div_clk%d", i + 1);

		spin_lock_init(&clkdiv[i].lock);
		clkdiv[i].base = start + i * 0x100;
		clkdiv[i].regmap = regmap;
		clkdiv[i].cxo_period_ns = NSEC_PER_SEC / cxo_hz;
		clkdiv[i].hw.init = &init;

		ret = devm_clk_hw_register(dev, &clkdiv[i].hw);
		if (ret)
			return ret;
	}

	return devm_of_clk_add_hw_provider(dev, spmi_pmic_div_clk_hw_get, cc);
}