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
struct regmap {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_fixed_args (struct device_node*,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int dra7xx_pcie_unaligned_memaccess(struct device *dev)
{
	int ret;
	struct device_node *np = dev->of_node;
	struct of_phandle_args args;
	struct regmap *regmap;

	regmap = syscon_regmap_lookup_by_phandle(np,
						 "ti,syscon-unaligned-access");
	if (IS_ERR(regmap)) {
		dev_dbg(dev, "can't get ti,syscon-unaligned-access\n");
		return -EINVAL;
	}

	ret = of_parse_phandle_with_fixed_args(np, "ti,syscon-unaligned-access",
					       2, 0, &args);
	if (ret) {
		dev_err(dev, "failed to parse ti,syscon-unaligned-access\n");
		return ret;
	}

	ret = regmap_update_bits(regmap, args.args[0], args.args[1],
				 args.args[1]);
	if (ret)
		dev_err(dev, "failed to enable unaligned access\n");

	of_node_put(args.np);

	return ret;
}