#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct tsi721_omsg_desc {void* next_hi; void* next_lo; scalar_t__ msg_info; void* type_id; } ;
struct tsi721_dma_sts {int dummy; } ;
struct tsi721_device {int flags; int* omsg_init; TYPE_2__* omsg_ring; TYPE_3__* pdev; scalar_t__ regs; TYPE_1__* msix; } ;
struct rio_mport {struct tsi721_device* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int size; int sts_size; struct tsi721_omsg_desc** omq_base; scalar_t__* omq_phys; struct tsi721_omsg_desc* omd_base; scalar_t__ omd_phys; struct tsi721_omsg_desc* sts_base; scalar_t__ sts_phys; scalar_t__ wr_count; scalar_t__ tx_slot; int /*<<< orphan*/  lock; scalar_t__ sts_rdptr; void* dev_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; int /*<<< orphan*/  irq_name; } ;

/* Variables and functions */
 int DTYPE5 ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OMSG ; 
 int RIO_MAX_MBOX ; 
 int TSI721_DMAC_DSSZ_SIZE (int) ; 
 int TSI721_MSG_BUFFER_SIZE ; 
 scalar_t__ TSI721_OBDMAC_CTL (int) ; 
 int TSI721_OBDMAC_CTL_INIT ; 
 int TSI721_OBDMAC_CTL_RETRY_THR ; 
 scalar_t__ TSI721_OBDMAC_DPTRH (int) ; 
 scalar_t__ TSI721_OBDMAC_DPTRL (int) ; 
 int TSI721_OBDMAC_DPTRL_MASK ; 
 scalar_t__ TSI721_OBDMAC_DSBH (int) ; 
 scalar_t__ TSI721_OBDMAC_DSBL (int) ; 
 int TSI721_OBDMAC_DSBL_MASK ; 
 scalar_t__ TSI721_OBDMAC_DSSZ (int) ; 
 scalar_t__ TSI721_OBDMAC_DWRCNT (int) ; 
 int /*<<< orphan*/  TSI721_OBDMAC_INT_ALL ; 
 int TSI721_OMSGD_MIN_RING_SIZE ; 
 int TSI721_OMSGD_RING_SIZE ; 
 int TSI721_USING_MSIX ; 
 int TSI721_VECT_OMB0_DONE ; 
 int TSI721_VECT_OMB0_INT ; 
 void* cpu_to_le32 (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct tsi721_omsg_desc*,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  mb () ; 
 int mbox_sel ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_omsg_interrupt_enable (struct tsi721_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi721_omsg_msix ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tsi721_open_outb_mbox(struct rio_mport *mport, void *dev_id,
				 int mbox, int entries)
{
	struct tsi721_device *priv = mport->priv;
	struct tsi721_omsg_desc *bd_ptr;
	int i, rc = 0;

	if ((entries < TSI721_OMSGD_MIN_RING_SIZE) ||
	    (entries > (TSI721_OMSGD_RING_SIZE)) ||
	    (!is_power_of_2(entries)) || mbox >= RIO_MAX_MBOX) {
		rc = -EINVAL;
		goto out;
	}

	if ((mbox_sel & (1 << mbox)) == 0) {
		rc = -ENODEV;
		goto out;
	}

	priv->omsg_ring[mbox].dev_id = dev_id;
	priv->omsg_ring[mbox].size = entries;
	priv->omsg_ring[mbox].sts_rdptr = 0;
	spin_lock_init(&priv->omsg_ring[mbox].lock);

	/* Outbound Msg Buffer allocation based on
	   the number of maximum descriptor entries */
	for (i = 0; i < entries; i++) {
		priv->omsg_ring[mbox].omq_base[i] =
			dma_alloc_coherent(
				&priv->pdev->dev, TSI721_MSG_BUFFER_SIZE,
				&priv->omsg_ring[mbox].omq_phys[i],
				GFP_KERNEL);
		if (priv->omsg_ring[mbox].omq_base[i] == NULL) {
			tsi_debug(OMSG, &priv->pdev->dev,
				  "ENOMEM for OB_MSG_%d data buffer", mbox);
			rc = -ENOMEM;
			goto out_buf;
		}
	}

	/* Outbound message descriptor allocation */
	priv->omsg_ring[mbox].omd_base = dma_alloc_coherent(
				&priv->pdev->dev,
				(entries + 1) * sizeof(struct tsi721_omsg_desc),
				&priv->omsg_ring[mbox].omd_phys, GFP_KERNEL);
	if (priv->omsg_ring[mbox].omd_base == NULL) {
		tsi_debug(OMSG, &priv->pdev->dev,
			"ENOMEM for OB_MSG_%d descriptor memory", mbox);
		rc = -ENOMEM;
		goto out_buf;
	}

	priv->omsg_ring[mbox].tx_slot = 0;

	/* Outbound message descriptor status FIFO allocation */
	priv->omsg_ring[mbox].sts_size = roundup_pow_of_two(entries + 1);
	priv->omsg_ring[mbox].sts_base = dma_alloc_coherent(&priv->pdev->dev,
							    priv->omsg_ring[mbox].sts_size * sizeof(struct tsi721_dma_sts),
							    &priv->omsg_ring[mbox].sts_phys,
							    GFP_KERNEL);
	if (priv->omsg_ring[mbox].sts_base == NULL) {
		tsi_debug(OMSG, &priv->pdev->dev,
			"ENOMEM for OB_MSG_%d status FIFO", mbox);
		rc = -ENOMEM;
		goto out_desc;
	}

	/*
	 * Configure Outbound Messaging Engine
	 */

	/* Setup Outbound Message descriptor pointer */
	iowrite32(((u64)priv->omsg_ring[mbox].omd_phys >> 32),
			priv->regs + TSI721_OBDMAC_DPTRH(mbox));
	iowrite32(((u64)priv->omsg_ring[mbox].omd_phys &
					TSI721_OBDMAC_DPTRL_MASK),
			priv->regs + TSI721_OBDMAC_DPTRL(mbox));

	/* Setup Outbound Message descriptor status FIFO */
	iowrite32(((u64)priv->omsg_ring[mbox].sts_phys >> 32),
			priv->regs + TSI721_OBDMAC_DSBH(mbox));
	iowrite32(((u64)priv->omsg_ring[mbox].sts_phys &
					TSI721_OBDMAC_DSBL_MASK),
			priv->regs + TSI721_OBDMAC_DSBL(mbox));
	iowrite32(TSI721_DMAC_DSSZ_SIZE(priv->omsg_ring[mbox].sts_size),
		priv->regs + (u32)TSI721_OBDMAC_DSSZ(mbox));

	/* Enable interrupts */

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		int idx = TSI721_VECT_OMB0_DONE + mbox;

		/* Request interrupt service if we are in MSI-X mode */
		rc = request_irq(priv->msix[idx].vector, tsi721_omsg_msix, 0,
				 priv->msix[idx].irq_name, (void *)priv);

		if (rc) {
			tsi_debug(OMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for OBOX%d-DONE",
				mbox);
			goto out_stat;
		}

		idx = TSI721_VECT_OMB0_INT + mbox;
		rc = request_irq(priv->msix[idx].vector, tsi721_omsg_msix, 0,
				 priv->msix[idx].irq_name, (void *)priv);

		if (rc)	{
			tsi_debug(OMSG, &priv->pdev->dev,
				"Unable to get MSI-X IRQ for MBOX%d-INT", mbox);
			idx = TSI721_VECT_OMB0_DONE + mbox;
			free_irq(priv->msix[idx].vector, (void *)priv);
			goto out_stat;
		}
	}
#endif /* CONFIG_PCI_MSI */

	tsi721_omsg_interrupt_enable(priv, mbox, TSI721_OBDMAC_INT_ALL);

	/* Initialize Outbound Message descriptors ring */
	bd_ptr = priv->omsg_ring[mbox].omd_base;
	bd_ptr[entries].type_id = cpu_to_le32(DTYPE5 << 29);
	bd_ptr[entries].msg_info = 0;
	bd_ptr[entries].next_lo =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omd_phys &
		TSI721_OBDMAC_DPTRL_MASK);
	bd_ptr[entries].next_hi =
		cpu_to_le32((u64)priv->omsg_ring[mbox].omd_phys >> 32);
	priv->omsg_ring[mbox].wr_count = 0;
	mb();

	/* Initialize Outbound Message engine */
	iowrite32(TSI721_OBDMAC_CTL_RETRY_THR | TSI721_OBDMAC_CTL_INIT,
		  priv->regs + TSI721_OBDMAC_CTL(mbox));
	ioread32(priv->regs + TSI721_OBDMAC_DWRCNT(mbox));
	udelay(10);

	priv->omsg_init[mbox] = 1;

	return 0;

#ifdef CONFIG_PCI_MSI
out_stat:
	dma_free_coherent(&priv->pdev->dev,
		priv->omsg_ring[mbox].sts_size * sizeof(struct tsi721_dma_sts),
		priv->omsg_ring[mbox].sts_base,
		priv->omsg_ring[mbox].sts_phys);

	priv->omsg_ring[mbox].sts_base = NULL;
#endif /* CONFIG_PCI_MSI */

out_desc:
	dma_free_coherent(&priv->pdev->dev,
		(entries + 1) * sizeof(struct tsi721_omsg_desc),
		priv->omsg_ring[mbox].omd_base,
		priv->omsg_ring[mbox].omd_phys);

	priv->omsg_ring[mbox].omd_base = NULL;

out_buf:
	for (i = 0; i < priv->omsg_ring[mbox].size; i++) {
		if (priv->omsg_ring[mbox].omq_base[i]) {
			dma_free_coherent(&priv->pdev->dev,
				TSI721_MSG_BUFFER_SIZE,
				priv->omsg_ring[mbox].omq_base[i],
				priv->omsg_ring[mbox].omq_phys[i]);

			priv->omsg_ring[mbox].omq_base[i] = NULL;
		}
	}

out:
	return rc;
}