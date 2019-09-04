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
struct TYPE_4__ {int of_reset_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct hisi_reset_controller {TYPE_1__ rcdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct hisi_reset_controller* devm_kmalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_reset_of_xlate ; 
 int /*<<< orphan*/  hisi_reset_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_controller_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct hisi_reset_controller *hisi_reset_init(struct platform_device *pdev)
{
	struct hisi_reset_controller *rstc;
	struct resource *res;

	rstc = devm_kmalloc(&pdev->dev, sizeof(*rstc), GFP_KERNEL);
	if (!rstc)
		return NULL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rstc->membase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rstc->membase))
		return NULL;

	spin_lock_init(&rstc->lock);
	rstc->rcdev.owner = THIS_MODULE;
	rstc->rcdev.ops = &hisi_reset_ops;
	rstc->rcdev.of_node = pdev->dev.of_node;
	rstc->rcdev.of_reset_n_cells = 2;
	rstc->rcdev.of_xlate = hisi_reset_of_xlate;
	reset_controller_register(&rstc->rcdev);

	return rstc;
}