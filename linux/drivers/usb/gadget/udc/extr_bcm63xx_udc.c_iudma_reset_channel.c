#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iudma_ch {int ch_idx; scalar_t__ ep_num; int /*<<< orphan*/  bd_ring_dma; scalar_t__ n_bds_used; struct bcm_enet_desc* bd_ring; struct bcm_enet_desc* write_bd; struct bcm_enet_desc* read_bd; struct bcm_enet_desc* end_bd; scalar_t__ is_tx; } ;
struct bcm_enet_desc {scalar_t__ len_stat; } ;
struct bcm63xx_udc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENETDMAC_CHANCFG_BUFHALT_MASK ; 
 int ENETDMAC_CHANCFG_EN_MASK ; 
 int /*<<< orphan*/  ENETDMAC_CHANCFG_REG ; 
 int /*<<< orphan*/  ENETDMAC_IRMASK_REG ; 
 int ENETDMAC_IR_BUFDONE_MASK ; 
 int /*<<< orphan*/  ENETDMAC_IR_REG ; 
 int /*<<< orphan*/  ENETDMAC_MAXBURST_REG ; 
 int /*<<< orphan*/  ENETDMAS_RSTART_REG ; 
 int /*<<< orphan*/  ENETDMAS_SRAM2_REG ; 
 int IUDMA_RESET_TIMEOUT_US ; 
 int /*<<< orphan*/  bcm63xx_fifo_reset_ep (struct bcm63xx_udc*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ max (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usb_dmac_readl (struct bcm63xx_udc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_dmac_writel (struct bcm63xx_udc*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_dmas_writel (struct bcm63xx_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iudma_reset_channel(struct bcm63xx_udc *udc, struct iudma_ch *iudma)
{
	int timeout = IUDMA_RESET_TIMEOUT_US;
	struct bcm_enet_desc *d;
	int ch_idx = iudma->ch_idx;

	if (!iudma->is_tx)
		bcm63xx_fifo_reset_ep(udc, max(0, iudma->ep_num));

	/* stop DMA, then wait for the hardware to wrap up */
	usb_dmac_writel(udc, 0, ENETDMAC_CHANCFG_REG, ch_idx);

	while (usb_dmac_readl(udc, ENETDMAC_CHANCFG_REG, ch_idx) &
				   ENETDMAC_CHANCFG_EN_MASK) {
		udelay(1);

		/* repeatedly flush the FIFO data until the BD completes */
		if (iudma->is_tx && iudma->ep_num >= 0)
			bcm63xx_fifo_reset_ep(udc, iudma->ep_num);

		if (!timeout--) {
			dev_err(udc->dev, "can't reset IUDMA channel %d\n",
				ch_idx);
			break;
		}
		if (timeout == IUDMA_RESET_TIMEOUT_US / 2) {
			dev_warn(udc->dev, "forcibly halting IUDMA channel %d\n",
				 ch_idx);
			usb_dmac_writel(udc, ENETDMAC_CHANCFG_BUFHALT_MASK,
					ENETDMAC_CHANCFG_REG, ch_idx);
		}
	}
	usb_dmac_writel(udc, ~0, ENETDMAC_IR_REG, ch_idx);

	/* don't leave "live" HW-owned entries for the next guy to step on */
	for (d = iudma->bd_ring; d <= iudma->end_bd; d++)
		d->len_stat = 0;
	mb();

	iudma->read_bd = iudma->write_bd = iudma->bd_ring;
	iudma->n_bds_used = 0;

	/* set up IRQs, UBUS burst size, and BD base for this channel */
	usb_dmac_writel(udc, ENETDMAC_IR_BUFDONE_MASK,
			ENETDMAC_IRMASK_REG, ch_idx);
	usb_dmac_writel(udc, 8, ENETDMAC_MAXBURST_REG, ch_idx);

	usb_dmas_writel(udc, iudma->bd_ring_dma, ENETDMAS_RSTART_REG, ch_idx);
	usb_dmas_writel(udc, 0, ENETDMAS_SRAM2_REG, ch_idx);
}