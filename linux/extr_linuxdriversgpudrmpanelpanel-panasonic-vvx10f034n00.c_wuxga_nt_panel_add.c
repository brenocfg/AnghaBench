#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct device* dev; int /*<<< orphan*/ * funcs; } ;
struct wuxga_nt_panel {TYPE_2__* backlight; TYPE_3__ base; TYPE_1__* dsi; int /*<<< orphan*/  supply; int /*<<< orphan*/ * mode; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_mode ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int drm_panel_add (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_panel_init (TYPE_3__*) ; 
 TYPE_2__* of_find_backlight_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wuxga_nt_panel_funcs ; 

__attribute__((used)) static int wuxga_nt_panel_add(struct wuxga_nt_panel *wuxga_nt)
{
	struct device *dev = &wuxga_nt->dsi->dev;
	struct device_node *np;
	int ret;

	wuxga_nt->mode = &default_mode;

	wuxga_nt->supply = devm_regulator_get(dev, "power");
	if (IS_ERR(wuxga_nt->supply))
		return PTR_ERR(wuxga_nt->supply);

	np = of_parse_phandle(dev->of_node, "backlight", 0);
	if (np) {
		wuxga_nt->backlight = of_find_backlight_by_node(np);
		of_node_put(np);

		if (!wuxga_nt->backlight)
			return -EPROBE_DEFER;
	}

	drm_panel_init(&wuxga_nt->base);
	wuxga_nt->base.funcs = &wuxga_nt_panel_funcs;
	wuxga_nt->base.dev = &wuxga_nt->dsi->dev;

	ret = drm_panel_add(&wuxga_nt->base);
	if (ret < 0)
		goto put_backlight;

	return 0;

put_backlight:
	if (wuxga_nt->backlight)
		put_device(&wuxga_nt->backlight->dev);

	return ret;
}