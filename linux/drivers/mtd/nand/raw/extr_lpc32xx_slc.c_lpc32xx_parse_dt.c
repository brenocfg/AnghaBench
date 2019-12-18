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
struct lpc32xx_nand_cfg_slc {int /*<<< orphan*/  wp_gpio; int /*<<< orphan*/  rsetup; int /*<<< orphan*/  rhold; int /*<<< orphan*/  rwidth; int /*<<< orphan*/  rdr_clks; int /*<<< orphan*/  wsetup; int /*<<< orphan*/  whold; int /*<<< orphan*/  wwidth; int /*<<< orphan*/  wdr_clks; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct lpc32xx_nand_cfg_slc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lpc32xx_nand_cfg_slc *lpc32xx_parse_dt(struct device *dev)
{
	struct lpc32xx_nand_cfg_slc *ncfg;
	struct device_node *np = dev->of_node;

	ncfg = devm_kzalloc(dev, sizeof(*ncfg), GFP_KERNEL);
	if (!ncfg)
		return NULL;

	of_property_read_u32(np, "nxp,wdr-clks", &ncfg->wdr_clks);
	of_property_read_u32(np, "nxp,wwidth", &ncfg->wwidth);
	of_property_read_u32(np, "nxp,whold", &ncfg->whold);
	of_property_read_u32(np, "nxp,wsetup", &ncfg->wsetup);
	of_property_read_u32(np, "nxp,rdr-clks", &ncfg->rdr_clks);
	of_property_read_u32(np, "nxp,rwidth", &ncfg->rwidth);
	of_property_read_u32(np, "nxp,rhold", &ncfg->rhold);
	of_property_read_u32(np, "nxp,rsetup", &ncfg->rsetup);

	if (!ncfg->wdr_clks || !ncfg->wwidth || !ncfg->whold ||
	    !ncfg->wsetup || !ncfg->rdr_clks || !ncfg->rwidth ||
	    !ncfg->rhold || !ncfg->rsetup) {
		dev_err(dev, "chip parameters not specified correctly\n");
		return NULL;
	}

	ncfg->wp_gpio = of_get_named_gpio(np, "gpios", 0);

	return ncfg;
}