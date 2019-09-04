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
struct jr_outentry {int dummy; } ;
struct device {int dummy; } ;
struct caam_drv_private_jr {int /*<<< orphan*/  entinfo; int /*<<< orphan*/  outring; int /*<<< orphan*/  inpring; TYPE_1__* rregs; int /*<<< orphan*/  irq; int /*<<< orphan*/  irqtask; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  outring_base; int /*<<< orphan*/  inpring_base; } ;

/* Variables and functions */
 int JOBR_DEPTH ; 
 int caam_reset_hw_jr (struct device*) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_reg64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caam_jr_shutdown(struct device *dev)
{
	struct caam_drv_private_jr *jrp = dev_get_drvdata(dev);
	dma_addr_t inpbusaddr, outbusaddr;
	int ret;

	ret = caam_reset_hw_jr(dev);

	tasklet_kill(&jrp->irqtask);

	/* Release interrupt */
	free_irq(jrp->irq, dev);

	/* Free rings */
	inpbusaddr = rd_reg64(&jrp->rregs->inpring_base);
	outbusaddr = rd_reg64(&jrp->rregs->outring_base);
	dma_free_coherent(dev, sizeof(dma_addr_t) * JOBR_DEPTH,
			  jrp->inpring, inpbusaddr);
	dma_free_coherent(dev, sizeof(struct jr_outentry) * JOBR_DEPTH,
			  jrp->outring, outbusaddr);
	kfree(jrp->entinfo);

	return ret;
}