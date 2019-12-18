#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tilcdc_module {int dummy; } ;
struct TYPE_9__ {struct tilcdc_module* platform_data; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct pinctrl {int dummy; } ;
struct panel_module {TYPE_1__* backlight; int /*<<< orphan*/  timings; int /*<<< orphan*/  info; struct tilcdc_module base; struct pinctrl* enable_gpio; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct pinctrl*) ; 
 int PTR_ERR (struct pinctrl*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct pinctrl* devm_gpiod_get_optional (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 struct panel_module* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl* devm_pinctrl_get_select_default (TYPE_2__*) ; 
 int /*<<< orphan*/  display_timings_release (int /*<<< orphan*/ ) ; 
 TYPE_1__* of_find_backlight_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_get_display_timings (struct device_node*) ; 
 int /*<<< orphan*/  of_get_panel_info (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panel_module_ops ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tilcdc_module_cleanup (struct tilcdc_module*) ; 
 int /*<<< orphan*/  tilcdc_module_init (struct tilcdc_module*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int panel_probe(struct platform_device *pdev)
{
	struct device_node *bl_node, *node = pdev->dev.of_node;
	struct panel_module *panel_mod;
	struct tilcdc_module *mod;
	struct pinctrl *pinctrl;
	int ret;

	/* bail out early if no DT data: */
	if (!node) {
		dev_err(&pdev->dev, "device-tree data is missing\n");
		return -ENXIO;
	}

	panel_mod = devm_kzalloc(&pdev->dev, sizeof(*panel_mod), GFP_KERNEL);
	if (!panel_mod)
		return -ENOMEM;

	bl_node = of_parse_phandle(node, "backlight", 0);
	if (bl_node) {
		panel_mod->backlight = of_find_backlight_by_node(bl_node);
		of_node_put(bl_node);

		if (!panel_mod->backlight)
			return -EPROBE_DEFER;

		dev_info(&pdev->dev, "found backlight\n");
	}

	panel_mod->enable_gpio = devm_gpiod_get_optional(&pdev->dev, "enable",
							 GPIOD_OUT_LOW);
	if (IS_ERR(panel_mod->enable_gpio)) {
		ret = PTR_ERR(panel_mod->enable_gpio);
		dev_err(&pdev->dev, "failed to request enable GPIO\n");
		goto fail_backlight;
	}

	if (panel_mod->enable_gpio)
		dev_info(&pdev->dev, "found enable GPIO\n");

	mod = &panel_mod->base;
	pdev->dev.platform_data = mod;

	tilcdc_module_init(mod, "panel", &panel_module_ops);

	pinctrl = devm_pinctrl_get_select_default(&pdev->dev);
	if (IS_ERR(pinctrl))
		dev_warn(&pdev->dev, "pins are not configured\n");

	panel_mod->timings = of_get_display_timings(node);
	if (!panel_mod->timings) {
		dev_err(&pdev->dev, "could not get panel timings\n");
		ret = -EINVAL;
		goto fail_free;
	}

	panel_mod->info = of_get_panel_info(node);
	if (!panel_mod->info) {
		dev_err(&pdev->dev, "could not get panel info\n");
		ret = -EINVAL;
		goto fail_timings;
	}

	return 0;

fail_timings:
	display_timings_release(panel_mod->timings);

fail_free:
	tilcdc_module_cleanup(mod);

fail_backlight:
	if (panel_mod->backlight)
		put_device(&panel_mod->backlight->dev);
	return ret;
}