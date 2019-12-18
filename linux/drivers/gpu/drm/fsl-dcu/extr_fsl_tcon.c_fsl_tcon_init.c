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
struct fsl_tcon {int /*<<< orphan*/  ipg_clk; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct fsl_tcon* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fsl_tcon_init_regmap (struct device*,struct fsl_tcon*,struct device_node*) ; 
 int /*<<< orphan*/  of_clk_get_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct fsl_tcon *fsl_tcon_init(struct device *dev)
{
	struct fsl_tcon *tcon;
	struct device_node *np;
	int ret;

	/* TCON node is not mandatory, some devices do not provide TCON */
	np = of_parse_phandle(dev->of_node, "fsl,tcon", 0);
	if (!np)
		return NULL;

	tcon = devm_kzalloc(dev, sizeof(*tcon), GFP_KERNEL);
	if (!tcon)
		goto err_node_put;

	ret = fsl_tcon_init_regmap(dev, tcon, np);
	if (ret) {
		dev_err(dev, "Couldn't create the TCON regmap\n");
		goto err_node_put;
	}

	tcon->ipg_clk = of_clk_get_by_name(np, "ipg");
	if (IS_ERR(tcon->ipg_clk)) {
		dev_err(dev, "Couldn't get the TCON bus clock\n");
		goto err_node_put;
	}

	ret = clk_prepare_enable(tcon->ipg_clk);
	if (ret) {
		dev_err(dev, "Couldn't enable the TCON clock\n");
		goto err_node_put;
	}

	of_node_put(np);
	dev_info(dev, "Using TCON in bypass mode\n");

	return tcon;

err_node_put:
	of_node_put(np);
	return NULL;
}