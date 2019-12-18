#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct device_node* of_node; TYPE_2__* dev; } ;
struct tegra_rgb {TYPE_1__ output; void* clk_parent; void* clk; struct tegra_dc* dc; } ;
struct tegra_dc {TYPE_1__* rgb; TYPE_2__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int clk_set_parent (void*,void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct tegra_rgb* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int tegra_output_probe (TYPE_1__*) ; 

int tegra_dc_rgb_probe(struct tegra_dc *dc)
{
	struct device_node *np;
	struct tegra_rgb *rgb;
	int err;

	np = of_get_child_by_name(dc->dev->of_node, "rgb");
	if (!np || !of_device_is_available(np))
		return -ENODEV;

	rgb = devm_kzalloc(dc->dev, sizeof(*rgb), GFP_KERNEL);
	if (!rgb)
		return -ENOMEM;

	rgb->output.dev = dc->dev;
	rgb->output.of_node = np;
	rgb->dc = dc;

	err = tegra_output_probe(&rgb->output);
	if (err < 0)
		return err;

	rgb->clk = devm_clk_get(dc->dev, NULL);
	if (IS_ERR(rgb->clk)) {
		dev_err(dc->dev, "failed to get clock\n");
		return PTR_ERR(rgb->clk);
	}

	rgb->clk_parent = devm_clk_get(dc->dev, "parent");
	if (IS_ERR(rgb->clk_parent)) {
		dev_err(dc->dev, "failed to get parent clock\n");
		return PTR_ERR(rgb->clk_parent);
	}

	err = clk_set_parent(rgb->clk, rgb->clk_parent);
	if (err < 0) {
		dev_err(dc->dev, "failed to set parent clock: %d\n", err);
		return err;
	}

	dc->rgb = &rgb->output;

	return 0;
}