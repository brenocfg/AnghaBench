#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct platform_device {int dummy; } ;
struct of_device_id {struct armada_variant* data; } ;
struct drm_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {TYPE_1__* driver; struct device_node* of_node; } ;
struct armada_variant {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_match_table; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int armada_drm_crtc_create (struct drm_device*,struct device*,struct resource*,int,struct armada_variant const*,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int
armada_lcd_bind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct drm_device *drm = data;
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	int irq = platform_get_irq(pdev, 0);
	const struct armada_variant *variant;
	struct device_node *port = NULL;

	if (irq < 0)
		return irq;

	if (!dev->of_node) {
		const struct platform_device_id *id;

		id = platform_get_device_id(pdev);
		if (!id)
			return -ENXIO;

		variant = (const struct armada_variant *)id->driver_data;
	} else {
		const struct of_device_id *match;
		struct device_node *np, *parent = dev->of_node;

		match = of_match_device(dev->driver->of_match_table, dev);
		if (!match)
			return -ENXIO;

		np = of_get_child_by_name(parent, "ports");
		if (np)
			parent = np;
		port = of_get_child_by_name(parent, "port");
		of_node_put(np);
		if (!port) {
			dev_err(dev, "no port node found in %pOF\n", parent);
			return -ENXIO;
		}

		variant = match->data;
	}

	return armada_drm_crtc_create(drm, dev, res, irq, variant, port);
}