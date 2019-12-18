#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int irq; int /*<<< orphan*/  cmd_complete; int /*<<< orphan*/  lock; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int intel_punit_get_bars (struct platform_device*) ; 
 int /*<<< orphan*/  intel_punit_ioc ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq_optional (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 TYPE_1__* punit_ipcdev ; 

__attribute__((used)) static int intel_punit_ipc_probe(struct platform_device *pdev)
{
	int irq, ret;

	punit_ipcdev = devm_kzalloc(&pdev->dev,
				    sizeof(*punit_ipcdev), GFP_KERNEL);
	if (!punit_ipcdev)
		return -ENOMEM;

	platform_set_drvdata(pdev, punit_ipcdev);

	irq = platform_get_irq_optional(pdev, 0);
	if (irq < 0) {
		dev_warn(&pdev->dev, "Invalid IRQ, using polling mode\n");
	} else {
		ret = devm_request_irq(&pdev->dev, irq, intel_punit_ioc,
				       IRQF_NO_SUSPEND, "intel_punit_ipc",
				       &punit_ipcdev);
		if (ret) {
			dev_err(&pdev->dev, "Failed to request irq: %d\n", irq);
			return ret;
		}
		punit_ipcdev->irq = irq;
	}

	ret = intel_punit_get_bars(pdev);
	if (ret)
		goto out;

	punit_ipcdev->dev = &pdev->dev;
	mutex_init(&punit_ipcdev->lock);
	init_completion(&punit_ipcdev->cmd_complete);

out:
	return ret;
}