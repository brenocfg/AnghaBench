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
struct vexpress_syscfg {int /*<<< orphan*/  base; int /*<<< orphan*/  funcs; TYPE_1__* dev; } ;
struct resource {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct vexpress_syscfg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* vexpress_config_bridge_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vexpress_syscfg*) ; 
 int /*<<< orphan*/  vexpress_syscfg_bridge_ops ; 

__attribute__((used)) static int vexpress_syscfg_probe(struct platform_device *pdev)
{
	struct vexpress_syscfg *syscfg;
	struct resource *res;
	struct device *bridge;

	syscfg = devm_kzalloc(&pdev->dev, sizeof(*syscfg), GFP_KERNEL);
	if (!syscfg)
		return -ENOMEM;
	syscfg->dev = &pdev->dev;
	INIT_LIST_HEAD(&syscfg->funcs);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	syscfg->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(syscfg->base))
		return PTR_ERR(syscfg->base);

	/* Must use dev.parent (MFD), as that's where DT phandle points at... */
	bridge = vexpress_config_bridge_register(pdev->dev.parent,
			&vexpress_syscfg_bridge_ops, syscfg);

	return PTR_ERR_OR_ZERO(bridge);
}