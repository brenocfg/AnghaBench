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
typedef  int /*<<< orphan*/  u32 ;
struct ts4800_ts {int /*<<< orphan*/  bit; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int ts4800_parse_dt(struct platform_device *pdev,
			   struct ts4800_ts *ts)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *syscon_np;
	u32 reg, bit;
	int error;

	syscon_np = of_parse_phandle(np, "syscon", 0);
	if (!syscon_np) {
		dev_err(dev, "no syscon property\n");
		return -ENODEV;
	}

	ts->regmap = syscon_node_to_regmap(syscon_np);
	of_node_put(syscon_np);
	if (IS_ERR(ts->regmap)) {
		dev_err(dev, "cannot get parent's regmap\n");
		return PTR_ERR(ts->regmap);
	}

	error = of_property_read_u32_index(np, "syscon", 1, &reg);
	if (error < 0) {
		dev_err(dev, "no offset in syscon\n");
		return error;
	}

	ts->reg = reg;

	error = of_property_read_u32_index(np, "syscon", 2, &bit);
	if (error < 0) {
		dev_err(dev, "no bit in syscon\n");
		return error;
	}

	ts->bit = BIT(bit);

	return 0;
}