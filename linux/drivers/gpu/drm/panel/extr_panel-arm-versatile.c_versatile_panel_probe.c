#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct versatile_panel_type {scalar_t__ ib2; int /*<<< orphan*/  name; int /*<<< orphan*/  magic; } ;
struct TYPE_3__ {int /*<<< orphan*/ * funcs; struct device* dev; } ;
struct versatile_panel {TYPE_1__ panel; struct regmap* ib2_map; struct versatile_panel_type const* panel_type; struct regmap* map; struct device* dev; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct versatile_panel_type*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  SYS_CLCD ; 
 int /*<<< orphan*/  SYS_CLCD_CLCDID_MASK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 struct versatile_panel* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int drm_panel_add (TYPE_1__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_1__*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_regmap_lookup_by_compatible (char*) ; 
 int /*<<< orphan*/  versatile_panel_drm_funcs ; 
 struct versatile_panel_type* versatile_panels ; 

__attribute__((used)) static int versatile_panel_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct versatile_panel *vpanel;
	struct device *parent;
	struct regmap *map;
	int ret;
	u32 val;
	int i;

	parent = dev->parent;
	if (!parent) {
		dev_err(dev, "no parent for versatile panel\n");
		return -ENODEV;
	}
	map = syscon_node_to_regmap(parent->of_node);
	if (IS_ERR(map)) {
		dev_err(dev, "no regmap for versatile panel parent\n");
		return PTR_ERR(map);
	}

	vpanel = devm_kzalloc(dev, sizeof(*vpanel), GFP_KERNEL);
	if (!vpanel)
		return -ENOMEM;

	ret = regmap_read(map, SYS_CLCD, &val);
	if (ret) {
		dev_err(dev, "cannot access syscon regs\n");
		return ret;
	}

	val &= SYS_CLCD_CLCDID_MASK;

	for (i = 0; i < ARRAY_SIZE(versatile_panels); i++) {
		const struct versatile_panel_type *pt;

		pt = &versatile_panels[i];
		if (pt->magic == val) {
			vpanel->panel_type = pt;
			break;
		}
	}

	/* No panel detected or VGA, let's leave this show */
	if (i == ARRAY_SIZE(versatile_panels)) {
		dev_info(dev, "no panel detected\n");
		return -ENODEV;
	}

	dev_info(dev, "detected: %s\n", vpanel->panel_type->name);
	vpanel->dev = dev;
	vpanel->map = map;

	/* Check if the panel is mounted on an IB2 daughterboard */
	if (vpanel->panel_type->ib2) {
		vpanel->ib2_map = syscon_regmap_lookup_by_compatible(
			"arm,versatile-ib2-syscon");
		if (IS_ERR(vpanel->ib2_map))
			vpanel->ib2_map = NULL;
		else
			dev_info(dev, "panel mounted on IB2 daughterboard\n");
	}

	drm_panel_init(&vpanel->panel);
	vpanel->panel.dev = dev;
	vpanel->panel.funcs = &versatile_panel_drm_funcs;

	return drm_panel_add(&vpanel->panel);
}