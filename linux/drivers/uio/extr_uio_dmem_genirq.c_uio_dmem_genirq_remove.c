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
struct uio_dmem_genirq_platdata {struct uio_dmem_genirq_platdata* uioinfo; int /*<<< orphan*/ * irqcontrol; int /*<<< orphan*/ * handler; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uio_dmem_genirq_platdata*) ; 
 struct uio_dmem_genirq_platdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_dmem_genirq_platdata*) ; 

__attribute__((used)) static int uio_dmem_genirq_remove(struct platform_device *pdev)
{
	struct uio_dmem_genirq_platdata *priv = platform_get_drvdata(pdev);

	uio_unregister_device(priv->uioinfo);
	pm_runtime_disable(&pdev->dev);

	priv->uioinfo->handler = NULL;
	priv->uioinfo->irqcontrol = NULL;

	/* kfree uioinfo for OF */
	if (pdev->dev.of_node)
		kfree(priv->uioinfo);

	kfree(priv);
	return 0;
}