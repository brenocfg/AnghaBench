#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int of_reset_n_cells; int /*<<< orphan*/  nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct hsdk_rst {TYPE_1__ rcdev; int /*<<< orphan*/  lock; void* regs_rst; void* regs_ctl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HSDK_MAX_RESETS ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct hsdk_rst* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsdk_reset_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int reset_controller_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hsdk_reset_probe(struct platform_device *pdev)
{
	struct hsdk_rst *rst;
	struct resource *mem;

	rst = devm_kzalloc(&pdev->dev, sizeof(*rst), GFP_KERNEL);
	if (!rst)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rst->regs_ctl = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rst->regs_ctl))
		return PTR_ERR(rst->regs_ctl);

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	rst->regs_rst = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(rst->regs_rst))
		return PTR_ERR(rst->regs_rst);

	spin_lock_init(&rst->lock);

	rst->rcdev.owner = THIS_MODULE;
	rst->rcdev.ops = &hsdk_reset_ops;
	rst->rcdev.of_node = pdev->dev.of_node;
	rst->rcdev.nr_resets = HSDK_MAX_RESETS;
	rst->rcdev.of_reset_n_cells = 1;

	return reset_controller_register(&rst->rcdev);
}