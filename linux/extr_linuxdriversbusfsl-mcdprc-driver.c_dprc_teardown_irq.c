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
struct fsl_mc_device_irq {TYPE_1__* msi_desc; } ;
struct fsl_mc_device {int /*<<< orphan*/  dev; struct fsl_mc_device_irq** irqs; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_dprc_irq (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 

__attribute__((used)) static void dprc_teardown_irq(struct fsl_mc_device *mc_dev)
{
	struct fsl_mc_device_irq *irq = mc_dev->irqs[0];

	(void)disable_dprc_irq(mc_dev);

	devm_free_irq(&mc_dev->dev, irq->msi_desc->irq, &mc_dev->dev);

	fsl_mc_free_irqs(mc_dev);
}