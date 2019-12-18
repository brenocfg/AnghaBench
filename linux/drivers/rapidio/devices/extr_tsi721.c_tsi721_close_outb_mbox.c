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
typedef  size_t u32 ;
struct tsi721_omsg_desc {int dummy; } ;
struct tsi721_dma_sts {int dummy; } ;
struct tsi721_device {int flags; TYPE_3__* omsg_ring; TYPE_2__* pdev; TYPE_1__* msix; scalar_t__* omsg_init; } ;
struct rio_mport {struct tsi721_device* priv; } ;
struct TYPE_6__ {int sts_size; int size; int /*<<< orphan*/ ** omq_base; int /*<<< orphan*/ * omq_phys; int /*<<< orphan*/ * omd_base; int /*<<< orphan*/  omd_phys; int /*<<< orphan*/ * sts_base; int /*<<< orphan*/  sts_phys; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int TSI721_MSG_BUFFER_SIZE ; 
 int /*<<< orphan*/  TSI721_OBDMAC_INT_ALL ; 
 int TSI721_USING_MSIX ; 
 int TSI721_VECT_OMB0_DONE ; 
 int TSI721_VECT_OMB0_INT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  tsi721_omsg_interrupt_disable (struct tsi721_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_close_outb_mbox(struct rio_mport *mport, int mbox)
{
	struct tsi721_device *priv = mport->priv;
	u32 i;

	if (!priv->omsg_init[mbox])
		return;
	priv->omsg_init[mbox] = 0;

	/* Disable Interrupts */

	tsi721_omsg_interrupt_disable(priv, mbox, TSI721_OBDMAC_INT_ALL);

#ifdef CONFIG_PCI_MSI
	if (priv->flags & TSI721_USING_MSIX) {
		free_irq(priv->msix[TSI721_VECT_OMB0_DONE + mbox].vector,
			 (void *)priv);
		free_irq(priv->msix[TSI721_VECT_OMB0_INT + mbox].vector,
			 (void *)priv);
	}
#endif /* CONFIG_PCI_MSI */

	/* Free OMSG Descriptor Status FIFO */
	dma_free_coherent(&priv->pdev->dev,
		priv->omsg_ring[mbox].sts_size * sizeof(struct tsi721_dma_sts),
		priv->omsg_ring[mbox].sts_base,
		priv->omsg_ring[mbox].sts_phys);

	priv->omsg_ring[mbox].sts_base = NULL;

	/* Free OMSG descriptors */
	dma_free_coherent(&priv->pdev->dev,
		(priv->omsg_ring[mbox].size + 1) *
			sizeof(struct tsi721_omsg_desc),
		priv->omsg_ring[mbox].omd_base,
		priv->omsg_ring[mbox].omd_phys);

	priv->omsg_ring[mbox].omd_base = NULL;

	/* Free message buffers */
	for (i = 0; i < priv->omsg_ring[mbox].size; i++) {
		if (priv->omsg_ring[mbox].omq_base[i]) {
			dma_free_coherent(&priv->pdev->dev,
				TSI721_MSG_BUFFER_SIZE,
				priv->omsg_ring[mbox].omq_base[i],
				priv->omsg_ring[mbox].omq_phys[i]);

			priv->omsg_ring[mbox].omq_base[i] = NULL;
		}
	}
}