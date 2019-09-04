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
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprc_irq0_handler ; 
 int /*<<< orphan*/  dprc_irq0_handler_thread ; 

__attribute__((used)) static int register_dprc_irq_handler(struct fsl_mc_device *mc_dev)
{
	int error;
	struct fsl_mc_device_irq *irq = mc_dev->irqs[0];

	/*
	 * NOTE: devm_request_threaded_irq() invokes the device-specific
	 * function that programs the MSI physically in the device
	 */
	error = devm_request_threaded_irq(&mc_dev->dev,
					  irq->msi_desc->irq,
					  dprc_irq0_handler,
					  dprc_irq0_handler_thread,
					  IRQF_NO_SUSPEND | IRQF_ONESHOT,
					  dev_name(&mc_dev->dev),
					  &mc_dev->dev);
	if (error < 0) {
		dev_err(&mc_dev->dev,
			"devm_request_threaded_irq() failed: %d\n",
			error);
		return error;
	}

	return 0;
}