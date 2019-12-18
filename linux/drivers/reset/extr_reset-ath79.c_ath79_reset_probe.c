#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_7__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct TYPE_9__ {int of_reset_n_cells; int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct ath79_reset {TYPE_1__ restart_nb; TYPE_3__ rcdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ath79_reset_ops ; 
 int /*<<< orphan*/  ath79_reset_restart_handler ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct ath79_reset* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_2__*,TYPE_3__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ath79_reset*) ; 
 int register_restart_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath79_reset_probe(struct platform_device *pdev)
{
	struct ath79_reset *ath79_reset;
	struct resource *res;
	int err;

	ath79_reset = devm_kzalloc(&pdev->dev,
				sizeof(*ath79_reset), GFP_KERNEL);
	if (!ath79_reset)
		return -ENOMEM;

	platform_set_drvdata(pdev, ath79_reset);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ath79_reset->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ath79_reset->base))
		return PTR_ERR(ath79_reset->base);

	spin_lock_init(&ath79_reset->lock);
	ath79_reset->rcdev.ops = &ath79_reset_ops;
	ath79_reset->rcdev.owner = THIS_MODULE;
	ath79_reset->rcdev.of_node = pdev->dev.of_node;
	ath79_reset->rcdev.of_reset_n_cells = 1;
	ath79_reset->rcdev.nr_resets = 32;

	err = devm_reset_controller_register(&pdev->dev, &ath79_reset->rcdev);
	if (err)
		return err;

	ath79_reset->restart_nb.notifier_call = ath79_reset_restart_handler;
	ath79_reset->restart_nb.priority = 128;

	err = register_restart_handler(&ath79_reset->restart_nb);
	if (err)
		dev_warn(&pdev->dev, "Failed to register restart handler\n");

	return 0;
}