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
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpio_irq_handler ; 
 scalar_t__ irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int register_dpio_irq_handlers(struct fsl_mc_device *dpio_dev, int cpu)
{
	int error;
	struct fsl_mc_device_irq *irq;
	cpumask_t mask;

	irq = dpio_dev->irqs[0];
	error = devm_request_irq(&dpio_dev->dev,
				 irq->msi_desc->irq,
				 dpio_irq_handler,
				 0,
				 dev_name(&dpio_dev->dev),
				 &dpio_dev->dev);
	if (error < 0) {
		dev_err(&dpio_dev->dev,
			"devm_request_irq() failed: %d\n",
			error);
		return error;
	}

	/* set the affinity hint */
	cpumask_clear(&mask);
	cpumask_set_cpu(cpu, &mask);
	if (irq_set_affinity_hint(irq->msi_desc->irq, &mask))
		dev_err(&dpio_dev->dev,
			"irq_set_affinity failed irq %d cpu %d\n",
			irq->msi_desc->irq, cpu);

	return 0;
}