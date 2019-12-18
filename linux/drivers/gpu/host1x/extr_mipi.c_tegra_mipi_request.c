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
struct tegra_mipi_device {int /*<<< orphan*/  pdev; struct device* device; int /*<<< orphan*/  pads; int /*<<< orphan*/  mipi; } ;
struct of_phandle_args {int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct tegra_mipi_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct tegra_mipi_device*) ; 
 struct tegra_mipi_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_find_device_by_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_drvdata (int /*<<< orphan*/ ) ; 

struct tegra_mipi_device *tegra_mipi_request(struct device *device)
{
	struct device_node *np = device->of_node;
	struct tegra_mipi_device *dev;
	struct of_phandle_args args;
	int err;

	err = of_parse_phandle_with_args(np, "nvidia,mipi-calibrate",
					 "#nvidia,mipi-calibrate-cells", 0,
					 &args);
	if (err < 0)
		return ERR_PTR(err);

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		err = -ENOMEM;
		goto out;
	}

	dev->pdev = of_find_device_by_node(args.np);
	if (!dev->pdev) {
		err = -ENODEV;
		goto free;
	}

	dev->mipi = platform_get_drvdata(dev->pdev);
	if (!dev->mipi) {
		err = -EPROBE_DEFER;
		goto put;
	}

	of_node_put(args.np);

	dev->pads = args.args[0];
	dev->device = device;

	return dev;

put:
	platform_device_put(dev->pdev);
free:
	kfree(dev);
out:
	of_node_put(args.np);
	return ERR_PTR(err);
}