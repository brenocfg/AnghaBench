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
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct axs10x_rst {TYPE_2__ rcdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  regs_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXS10X_MAX_RESETS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  axs10x_reset_ops ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct axs10x_rst* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_2__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axs10x_reset_probe(struct platform_device *pdev)
{
	struct axs10x_rst *rst;
	struct resource *mem;

	rst = devm_kzalloc(&pdev->dev, sizeof(*rst), GFP_KERNEL);
	if (!rst)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rst->regs_rst = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rst->regs_rst))
		return PTR_ERR(rst->regs_rst);

	spin_lock_init(&rst->lock);

	rst->rcdev.owner = THIS_MODULE;
	rst->rcdev.ops = &axs10x_reset_ops;
	rst->rcdev.of_node = pdev->dev.of_node;
	rst->rcdev.nr_resets = AXS10X_MAX_RESETS;

	return devm_reset_controller_register(&pdev->dev, &rst->rcdev);
}