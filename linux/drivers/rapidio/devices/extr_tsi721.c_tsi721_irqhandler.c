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
typedef  int u32 ;
struct tsi721_device {int flags; scalar_t__ regs; int /*<<< orphan*/ * bdma; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int /*<<< orphan*/  IDB_QUEUE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RIO_MAX_MBOX ; 
 scalar_t__ TSI721_DEV_CHAN_INT ; 
 scalar_t__ TSI721_DEV_CHAN_INTE ; 
 scalar_t__ TSI721_DEV_INT ; 
 scalar_t__ TSI721_DEV_INTE ; 
 int TSI721_DEV_INT_BDMA_CH ; 
 int TSI721_DEV_INT_SMSG_CH ; 
 int TSI721_DEV_INT_SR2PC_CH ; 
 int TSI721_DEV_INT_SRIO ; 
 int TSI721_DMA_MAXCH ; 
 int TSI721_INT_BDMA_CHAN (int) ; 
 int TSI721_INT_BDMA_CHAN_M ; 
 int TSI721_INT_IMSG_CHAN (int) ; 
 int TSI721_INT_IMSG_CHAN_M ; 
 int TSI721_INT_OMSG_CHAN (int) ; 
 int TSI721_INT_OMSG_CHAN_M ; 
 int TSI721_INT_SR2PC_CHAN (int /*<<< orphan*/ ) ; 
 scalar_t__ TSI721_RIO_EM_INT_STAT ; 
 int TSI721_RIO_EM_INT_STAT_PW_RX ; 
 scalar_t__ TSI721_SR_CHINT (int /*<<< orphan*/ ) ; 
 int TSI721_SR_CHINT_IDBQRCV ; 
 int TSI721_USING_MSI ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  tsi721_bdma_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi721_dbell_handler (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi721_imsg_handler (struct tsi721_device*,int) ; 
 int /*<<< orphan*/  tsi721_omsg_handler (struct tsi721_device*,int) ; 
 int /*<<< orphan*/  tsi721_pw_handler (struct tsi721_device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  tsi_info (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static irqreturn_t tsi721_irqhandler(int irq, void *ptr)
{
	struct tsi721_device *priv = (struct tsi721_device *)ptr;
	u32 dev_int;
	u32 dev_ch_int;
	u32 intval;
	u32 ch_inte;

	/* For MSI mode disable all device-level interrupts */
	if (priv->flags & TSI721_USING_MSI)
		iowrite32(0, priv->regs + TSI721_DEV_INTE);

	dev_int = ioread32(priv->regs + TSI721_DEV_INT);
	if (!dev_int)
		return IRQ_NONE;

	dev_ch_int = ioread32(priv->regs + TSI721_DEV_CHAN_INT);

	if (dev_int & TSI721_DEV_INT_SR2PC_CH) {
		/* Service SR2PC Channel interrupts */
		if (dev_ch_int & TSI721_INT_SR2PC_CHAN(IDB_QUEUE)) {
			/* Service Inbound Doorbell interrupt */
			intval = ioread32(priv->regs +
						TSI721_SR_CHINT(IDB_QUEUE));
			if (intval & TSI721_SR_CHINT_IDBQRCV)
				tsi721_dbell_handler(priv);
			else
				tsi_info(&priv->pdev->dev,
					"Unsupported SR_CH_INT %x", intval);

			/* Clear interrupts */
			iowrite32(intval,
				priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
			ioread32(priv->regs + TSI721_SR_CHINT(IDB_QUEUE));
		}
	}

	if (dev_int & TSI721_DEV_INT_SMSG_CH) {
		int ch;

		/*
		 * Service channel interrupts from Messaging Engine
		 */

		if (dev_ch_int & TSI721_INT_IMSG_CHAN_M) { /* Inbound Msg */
			/* Disable signaled OB MSG Channel interrupts */
			ch_inte = ioread32(priv->regs + TSI721_DEV_CHAN_INTE);
			ch_inte &= ~(dev_ch_int & TSI721_INT_IMSG_CHAN_M);
			iowrite32(ch_inte, priv->regs + TSI721_DEV_CHAN_INTE);

			/*
			 * Process Inbound Message interrupt for each MBOX
			 */
			for (ch = 4; ch < RIO_MAX_MBOX + 4; ch++) {
				if (!(dev_ch_int & TSI721_INT_IMSG_CHAN(ch)))
					continue;
				tsi721_imsg_handler(priv, ch);
			}
		}

		if (dev_ch_int & TSI721_INT_OMSG_CHAN_M) { /* Outbound Msg */
			/* Disable signaled OB MSG Channel interrupts */
			ch_inte = ioread32(priv->regs + TSI721_DEV_CHAN_INTE);
			ch_inte &= ~(dev_ch_int & TSI721_INT_OMSG_CHAN_M);
			iowrite32(ch_inte, priv->regs + TSI721_DEV_CHAN_INTE);

			/*
			 * Process Outbound Message interrupts for each MBOX
			 */

			for (ch = 0; ch < RIO_MAX_MBOX; ch++) {
				if (!(dev_ch_int & TSI721_INT_OMSG_CHAN(ch)))
					continue;
				tsi721_omsg_handler(priv, ch);
			}
		}
	}

	if (dev_int & TSI721_DEV_INT_SRIO) {
		/* Service SRIO MAC interrupts */
		intval = ioread32(priv->regs + TSI721_RIO_EM_INT_STAT);
		if (intval & TSI721_RIO_EM_INT_STAT_PW_RX)
			tsi721_pw_handler(priv);
	}

#ifdef CONFIG_RAPIDIO_DMA_ENGINE
	if (dev_int & TSI721_DEV_INT_BDMA_CH) {
		int ch;

		if (dev_ch_int & TSI721_INT_BDMA_CHAN_M) {
			tsi_debug(DMA, &priv->pdev->dev,
				  "IRQ from DMA channel 0x%08x", dev_ch_int);

			for (ch = 0; ch < TSI721_DMA_MAXCH; ch++) {
				if (!(dev_ch_int & TSI721_INT_BDMA_CHAN(ch)))
					continue;
				tsi721_bdma_handler(&priv->bdma[ch]);
			}
		}
	}
#endif

	/* For MSI mode re-enable device-level interrupts */
	if (priv->flags & TSI721_USING_MSI) {
		dev_int = TSI721_DEV_INT_SR2PC_CH | TSI721_DEV_INT_SRIO |
			TSI721_DEV_INT_SMSG_CH | TSI721_DEV_INT_BDMA_CH;
		iowrite32(dev_int, priv->regs + TSI721_DEV_INTE);
	}

	return IRQ_HANDLED;
}