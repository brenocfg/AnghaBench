#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jr_outentry {int dummy; } ;
struct device {int dummy; } ;
struct caam_drv_private_jr {int ringsize; int /*<<< orphan*/  irqtask; int /*<<< orphan*/  irq; int /*<<< orphan*/  ridx; void* inpring; void* outring; TYPE_1__* rregs; int /*<<< orphan*/  outlock; int /*<<< orphan*/  inplock; scalar_t__ tail; scalar_t__ head; scalar_t__ out_ring_read_index; scalar_t__ inp_ring_write_index; TYPE_2__* entinfo; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int desc_addr_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  rconfig_lo; int /*<<< orphan*/  outring_size; int /*<<< orphan*/  inpring_size; int /*<<< orphan*/  outring_base; int /*<<< orphan*/  inpring_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int JOBR_DEPTH ; 
 int JOBR_INTC ; 
 int JOBR_INTC_COUNT_THLD ; 
 int JOBR_INTC_TIME_THLD ; 
 int JRCFG_ICDCT_SHIFT ; 
 int JRCFG_ICTT_SHIFT ; 
 int /*<<< orphan*/  caam_jr_dequeue ; 
 int /*<<< orphan*/  caam_jr_interrupt ; 
 int caam_reset_hw_jr (struct device*) ; 
 int /*<<< orphan*/  clrsetbits_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wr_reg64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int caam_jr_init(struct device *dev)
{
	struct caam_drv_private_jr *jrp;
	dma_addr_t inpbusaddr, outbusaddr;
	int i, error;

	jrp = dev_get_drvdata(dev);

	tasklet_init(&jrp->irqtask, caam_jr_dequeue, (unsigned long)dev);

	/* Connect job ring interrupt handler. */
	error = request_irq(jrp->irq, caam_jr_interrupt, IRQF_SHARED,
			    dev_name(dev), dev);
	if (error) {
		dev_err(dev, "can't connect JobR %d interrupt (%d)\n",
			jrp->ridx, jrp->irq);
		goto out_kill_deq;
	}

	error = caam_reset_hw_jr(dev);
	if (error)
		goto out_free_irq;

	error = -ENOMEM;
	jrp->inpring = dma_alloc_coherent(dev, sizeof(*jrp->inpring) *
					  JOBR_DEPTH, &inpbusaddr, GFP_KERNEL);
	if (!jrp->inpring)
		goto out_free_irq;

	jrp->outring = dma_alloc_coherent(dev, sizeof(*jrp->outring) *
					  JOBR_DEPTH, &outbusaddr, GFP_KERNEL);
	if (!jrp->outring)
		goto out_free_inpring;

	jrp->entinfo = kcalloc(JOBR_DEPTH, sizeof(*jrp->entinfo), GFP_KERNEL);
	if (!jrp->entinfo)
		goto out_free_outring;

	for (i = 0; i < JOBR_DEPTH; i++)
		jrp->entinfo[i].desc_addr_dma = !0;

	/* Setup rings */
	jrp->inp_ring_write_index = 0;
	jrp->out_ring_read_index = 0;
	jrp->head = 0;
	jrp->tail = 0;

	wr_reg64(&jrp->rregs->inpring_base, inpbusaddr);
	wr_reg64(&jrp->rregs->outring_base, outbusaddr);
	wr_reg32(&jrp->rregs->inpring_size, JOBR_DEPTH);
	wr_reg32(&jrp->rregs->outring_size, JOBR_DEPTH);

	jrp->ringsize = JOBR_DEPTH;

	spin_lock_init(&jrp->inplock);
	spin_lock_init(&jrp->outlock);

	/* Select interrupt coalescing parameters */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JOBR_INTC |
		      (JOBR_INTC_COUNT_THLD << JRCFG_ICDCT_SHIFT) |
		      (JOBR_INTC_TIME_THLD << JRCFG_ICTT_SHIFT));

	return 0;

out_free_outring:
	dma_free_coherent(dev, sizeof(struct jr_outentry) * JOBR_DEPTH,
			  jrp->outring, outbusaddr);
out_free_inpring:
	dma_free_coherent(dev, sizeof(dma_addr_t) * JOBR_DEPTH,
			  jrp->inpring, inpbusaddr);
	dev_err(dev, "can't allocate job rings for %d\n", jrp->ridx);
out_free_irq:
	free_irq(jrp->irq, dev);
out_kill_deq:
	tasklet_kill(&jrp->irqtask);
	return error;
}