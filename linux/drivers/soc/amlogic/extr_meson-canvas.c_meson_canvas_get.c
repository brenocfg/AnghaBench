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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct meson_canvas {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct meson_canvas* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct meson_canvas* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

struct meson_canvas *meson_canvas_get(struct device *dev)
{
	struct device_node *canvas_node;
	struct platform_device *canvas_pdev;
	struct meson_canvas *canvas;

	canvas_node = of_parse_phandle(dev->of_node, "amlogic,canvas", 0);
	if (!canvas_node)
		return ERR_PTR(-ENODEV);

	canvas_pdev = of_find_device_by_node(canvas_node);
	if (!canvas_pdev) {
		of_node_put(canvas_node);
		return ERR_PTR(-EPROBE_DEFER);
	}

	of_node_put(canvas_node);

	/*
	 * If priv is NULL, it's probably because the canvas hasn't
	 * properly initialized. Bail out with -EINVAL because, in the
	 * current state, this driver probe cannot return -EPROBE_DEFER
	 */
	canvas = dev_get_drvdata(&canvas_pdev->dev);
	if (!canvas)
		return ERR_PTR(-EINVAL);

	return canvas;
}