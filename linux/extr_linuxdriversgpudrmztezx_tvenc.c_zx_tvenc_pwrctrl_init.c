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
struct zx_tvenc_pwrctrl {int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; struct regmap* regmap; } ;
struct zx_tvenc {struct device* dev; struct zx_tvenc_pwrctrl pwrctrl; } ;
struct regmap {int dummy; } ;
struct of_phandle_args {int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_fixed_args (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_tvenc_pwrctrl_init(struct zx_tvenc *tvenc)
{
	struct zx_tvenc_pwrctrl *pwrctrl = &tvenc->pwrctrl;
	struct device *dev = tvenc->dev;
	struct of_phandle_args out_args;
	struct regmap *regmap;
	int ret;

	ret = of_parse_phandle_with_fixed_args(dev->of_node,
				"zte,tvenc-power-control", 2, 0, &out_args);
	if (ret)
		return ret;

	regmap = syscon_node_to_regmap(out_args.np);
	if (IS_ERR(regmap)) {
		ret = PTR_ERR(regmap);
		goto out;
	}

	pwrctrl->regmap = regmap;
	pwrctrl->reg = out_args.args[0];
	pwrctrl->mask = out_args.args[1];

out:
	of_node_put(out_args.np);
	return ret;
}