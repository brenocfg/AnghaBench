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
struct lpc32xx_nand_cfg_mlc {int /*<<< orphan*/  wp_gpio; int /*<<< orphan*/  wr_low; int /*<<< orphan*/  wr_high; int /*<<< orphan*/  rd_low; int /*<<< orphan*/  rd_high; int /*<<< orphan*/  nand_ta; int /*<<< orphan*/  busy_delay; int /*<<< orphan*/  tcea_delay; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct lpc32xx_nand_cfg_mlc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct lpc32xx_nand_cfg_mlc *lpc32xx_parse_dt(struct device *dev)
{
	struct lpc32xx_nand_cfg_mlc *ncfg;
	struct device_node *np = dev->of_node;

	ncfg = devm_kzalloc(dev, sizeof(*ncfg), GFP_KERNEL);
	if (!ncfg)
		return NULL;

	of_property_read_u32(np, "nxp,tcea-delay", &ncfg->tcea_delay);
	of_property_read_u32(np, "nxp,busy-delay", &ncfg->busy_delay);
	of_property_read_u32(np, "nxp,nand-ta", &ncfg->nand_ta);
	of_property_read_u32(np, "nxp,rd-high", &ncfg->rd_high);
	of_property_read_u32(np, "nxp,rd-low", &ncfg->rd_low);
	of_property_read_u32(np, "nxp,wr-high", &ncfg->wr_high);
	of_property_read_u32(np, "nxp,wr-low", &ncfg->wr_low);

	if (!ncfg->tcea_delay || !ncfg->busy_delay || !ncfg->nand_ta ||
	    !ncfg->rd_high || !ncfg->rd_low || !ncfg->wr_high ||
	    !ncfg->wr_low) {
		dev_err(dev, "chip parameters not specified correctly\n");
		return NULL;
	}

	ncfg->wp_gpio = of_get_named_gpio(np, "gpios", 0);

	return ncfg;
}