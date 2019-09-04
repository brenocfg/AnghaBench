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
struct videomode {int dummy; } ;
struct exynos_dpi {int /*<<< orphan*/  panel_node; struct videomode* vm; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIMD_PORT_RGB ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct videomode*) ; 
 struct videomode* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_get_videomode (struct device_node*,struct videomode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_graph_get_remote_node (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int exynos_dpi_parse_dt(struct exynos_dpi *ctx)
{
	struct device *dev = ctx->dev;
	struct device_node *dn = dev->of_node;
	struct device_node *np;

	ctx->panel_node = of_graph_get_remote_node(dn, FIMD_PORT_RGB, 0);

	np = of_get_child_by_name(dn, "display-timings");
	if (np) {
		struct videomode *vm;
		int ret;

		of_node_put(np);

		vm = devm_kzalloc(dev, sizeof(*ctx->vm), GFP_KERNEL);
		if (!vm)
			return -ENOMEM;

		ret = of_get_videomode(dn, vm, 0);
		if (ret < 0) {
			devm_kfree(dev, vm);
			return ret;
		}

		ctx->vm = vm;

		return 0;
	}

	if (!ctx->panel_node)
		return -EINVAL;

	return 0;
}