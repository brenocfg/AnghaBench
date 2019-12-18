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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pl111_drm_dev_private {int /*<<< orphan*/ * variant; int /*<<< orphan*/  variant_display_disable; int /*<<< orphan*/  variant_display_enable; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  ienb; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
typedef  enum versatile_clcd { ____Placeholder_versatile_clcd } versatile_clcd ;

/* Variables and functions */
 int /*<<< orphan*/  CLCD_PL111_CNTL ; 
 int /*<<< orphan*/  CLCD_PL111_IENB ; 
 int EPROBE_DEFER ; 
#define  INTEGRATOR_CLCD_CM 135 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
#define  REALVIEW_CLCD_EB 134 
#define  REALVIEW_CLCD_PB1176 133 
#define  REALVIEW_CLCD_PB11MP 132 
#define  REALVIEW_CLCD_PBA8 131 
#define  REALVIEW_CLCD_PBX 130 
#define  VERSATILE_CLCD 129 
#define  VEXPRESS_CLCD_V2M 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct regmap* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_find_matching_node_and_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct of_device_id const**) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  pl110_integrator ; 
 int /*<<< orphan*/  pl110_versatile ; 
 int /*<<< orphan*/  pl111_integrator_enable ; 
 int /*<<< orphan*/  pl111_realview ; 
 int /*<<< orphan*/  pl111_realview_clcd_disable ; 
 int /*<<< orphan*/  pl111_realview_clcd_enable ; 
 int /*<<< orphan*/  pl111_versatile_disable ; 
 int /*<<< orphan*/  pl111_versatile_enable ; 
 int /*<<< orphan*/  pl111_vexpress ; 
 int pl111_vexpress_clcd_init (struct device*,struct pl111_drm_dev_private*,struct regmap*) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 
 int /*<<< orphan*/  versatile_clcd_of_match ; 
 struct regmap* versatile_syscon_map ; 
 int vexpress_muxfpga_init () ; 

int pl111_versatile_init(struct device *dev, struct pl111_drm_dev_private *priv)
{
	const struct of_device_id *clcd_id;
	enum versatile_clcd versatile_clcd_type;
	struct device_node *np;
	struct regmap *map;
	int ret;

	np = of_find_matching_node_and_match(NULL, versatile_clcd_of_match,
					     &clcd_id);
	if (!np) {
		/* Non-ARM reference designs, just bail out */
		return 0;
	}
	versatile_clcd_type = (enum versatile_clcd)clcd_id->data;

	/* Versatile Express special handling */
	if (versatile_clcd_type == VEXPRESS_CLCD_V2M) {
		struct platform_device *pdev;

		/* Registers a driver for the muxfpga */
		ret = vexpress_muxfpga_init();
		if (ret) {
			dev_err(dev, "unable to initialize muxfpga driver\n");
			of_node_put(np);
			return ret;
		}

		/* Call into deep Vexpress configuration API */
		pdev = of_find_device_by_node(np);
		if (!pdev) {
			dev_err(dev, "can't find the sysreg device, deferring\n");
			of_node_put(np);
			return -EPROBE_DEFER;
		}
		map = dev_get_drvdata(&pdev->dev);
		if (!map) {
			dev_err(dev, "sysreg has not yet probed\n");
			platform_device_put(pdev);
			of_node_put(np);
			return -EPROBE_DEFER;
		}
	} else {
		map = syscon_node_to_regmap(np);
	}
	of_node_put(np);

	if (IS_ERR(map)) {
		dev_err(dev, "no Versatile syscon regmap\n");
		return PTR_ERR(map);
	}

	switch (versatile_clcd_type) {
	case INTEGRATOR_CLCD_CM:
		versatile_syscon_map = map;
		priv->variant = &pl110_integrator;
		priv->variant_display_enable = pl111_integrator_enable;
		dev_info(dev, "set up callbacks for Integrator PL110\n");
		break;
	case VERSATILE_CLCD:
		versatile_syscon_map = map;
		/* This can do RGB565 with external PLD */
		priv->variant = &pl110_versatile;
		priv->variant_display_enable = pl111_versatile_enable;
		priv->variant_display_disable = pl111_versatile_disable;
		/*
		 * The Versatile has a variant halfway between PL110
		 * and PL111 where these two registers have already been
		 * swapped.
		 */
		priv->ienb = CLCD_PL111_IENB;
		priv->ctrl = CLCD_PL111_CNTL;
		dev_info(dev, "set up callbacks for Versatile PL110\n");
		break;
	case REALVIEW_CLCD_EB:
	case REALVIEW_CLCD_PB1176:
	case REALVIEW_CLCD_PB11MP:
	case REALVIEW_CLCD_PBA8:
	case REALVIEW_CLCD_PBX:
		versatile_syscon_map = map;
		priv->variant = &pl111_realview;
		priv->variant_display_enable = pl111_realview_clcd_enable;
		priv->variant_display_disable = pl111_realview_clcd_disable;
		dev_info(dev, "set up callbacks for RealView PL111\n");
		break;
	case VEXPRESS_CLCD_V2M:
		priv->variant = &pl111_vexpress;
		dev_info(dev, "initializing Versatile Express PL111\n");
		ret = pl111_vexpress_clcd_init(dev, priv, map);
		if (ret)
			return ret;
		break;
	default:
		dev_info(dev, "unknown Versatile system controller\n");
		break;
	}

	return 0;
}