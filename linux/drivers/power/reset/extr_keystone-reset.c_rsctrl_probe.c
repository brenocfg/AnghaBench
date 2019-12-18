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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOVERFLOW ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int RSCFG_RG ; 
 int RSCFG_RSTYPE_HARD ; 
 int RSCFG_RSTYPE_SOFT ; 
 int RSISO_RG ; 
 int RSMUX_LOCK_SET ; 
 int /*<<< orphan*/  RSMUX_OMODE_MASK ; 
 int RSMUX_OMODE_RESET_ON ; 
 int WDT_MUX_NUMBER ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 struct regmap* pllctrl_regs ; 
 int register_restart_handler (int /*<<< orphan*/ *) ; 
 int regmap_update_bits (struct regmap*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int regmap_write (struct regmap*,int,int) ; 
 int rsctrl_enable_rspll_write () ; 
 int /*<<< orphan*/  rsctrl_restart_nb ; 
 int rspll_offset ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rsctrl_probe(struct platform_device *pdev)
{
	int i;
	int ret;
	u32 val;
	unsigned int rg;
	u32 rsmux_offset;
	struct regmap *devctrl_regs;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;

	if (!np)
		return -ENODEV;

	/* get regmaps */
	pllctrl_regs = syscon_regmap_lookup_by_phandle(np, "ti,syscon-pll");
	if (IS_ERR(pllctrl_regs))
		return PTR_ERR(pllctrl_regs);

	devctrl_regs = syscon_regmap_lookup_by_phandle(np, "ti,syscon-dev");
	if (IS_ERR(devctrl_regs))
		return PTR_ERR(devctrl_regs);

	ret = of_property_read_u32_index(np, "ti,syscon-pll", 1, &rspll_offset);
	if (ret) {
		dev_err(dev, "couldn't read the reset pll offset!\n");
		return -EINVAL;
	}

	ret = of_property_read_u32_index(np, "ti,syscon-dev", 1, &rsmux_offset);
	if (ret) {
		dev_err(dev, "couldn't read the rsmux offset!\n");
		return -EINVAL;
	}

	/* set soft/hard reset */
	val = of_property_read_bool(np, "ti,soft-reset");
	val = val ? RSCFG_RSTYPE_SOFT : RSCFG_RSTYPE_HARD;

	ret = rsctrl_enable_rspll_write();
	if (ret)
		return ret;

	ret = regmap_write(pllctrl_regs, rspll_offset + RSCFG_RG, val);
	if (ret)
		return ret;

	/* disable a reset isolation for all module clocks */
	ret = regmap_write(pllctrl_regs, rspll_offset + RSISO_RG, 0);
	if (ret)
		return ret;

	/* enable a reset for watchdogs from wdt-list */
	for (i = 0; i < WDT_MUX_NUMBER; i++) {
		ret = of_property_read_u32_index(np, "ti,wdt-list", i, &val);
		if (ret == -EOVERFLOW && !i) {
			dev_err(dev, "ti,wdt-list property has to contain at"
				"least one entry\n");
			return -EINVAL;
		} else if (ret) {
			break;
		}

		if (val >= WDT_MUX_NUMBER) {
			dev_err(dev, "ti,wdt-list property can contain "
				"only numbers < 4\n");
			return -EINVAL;
		}

		rg = rsmux_offset + val * 4;

		ret = regmap_update_bits(devctrl_regs, rg, RSMUX_OMODE_MASK,
					 RSMUX_OMODE_RESET_ON |
					 RSMUX_LOCK_SET);
		if (ret)
			return ret;
	}

	ret = register_restart_handler(&rsctrl_restart_nb);
	if (ret)
		dev_err(dev, "cannot register restart handler (err=%d)\n", ret);

	return ret;
}