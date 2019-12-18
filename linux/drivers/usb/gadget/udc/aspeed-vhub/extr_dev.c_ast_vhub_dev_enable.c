#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {int stalled; int wedged; } ;
struct ast_vhub_ep {TYPE_4__ epn; } ;
struct TYPE_7__ {size_t buf_dma; } ;
struct TYPE_5__ {scalar_t__ speed; } ;
struct ast_vhub_dev {int enabled; size_t index; int wakeup_en; struct ast_vhub_ep** epns; scalar_t__ regs; TYPE_3__ ep0; TYPE_2__* vhub; TYPE_1__ gadget; } ;
struct TYPE_6__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ AST_VHUB_DEV_EN_CTRL ; 
 scalar_t__ AST_VHUB_DEV_EP0_DATA ; 
 scalar_t__ AST_VHUB_IER ; 
 size_t AST_VHUB_NUM_GEN_EPs ; 
 scalar_t__ USB_SPEED_HIGH ; 
 size_t VHUB_DEV_EN_ENABLE_PORT ; 
 size_t VHUB_DEV_EN_EP0_IN_ACK_IRQEN ; 
 size_t VHUB_DEV_EN_EP0_OUT_ACK_IRQEN ; 
 size_t VHUB_DEV_EN_EP0_SETUP_IRQEN ; 
 size_t VHUB_DEV_EN_SPEED_SEL_HIGH ; 
 size_t VHUB_IRQ_DEVICE1 ; 
 int /*<<< orphan*/  ast_vhub_reset_ep0 (struct ast_vhub_dev*) ; 
 int /*<<< orphan*/  ast_vhub_update_epn_stall (struct ast_vhub_ep*) ; 
 size_t readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static void ast_vhub_dev_enable(struct ast_vhub_dev *d)
{
	u32 reg, hmsk, i;

	if (d->enabled)
		return;

	/* Cleanup EP0 state */
	ast_vhub_reset_ep0(d);

	/* Enable device and its EP0 interrupts */
	reg = VHUB_DEV_EN_ENABLE_PORT |
		VHUB_DEV_EN_EP0_IN_ACK_IRQEN |
		VHUB_DEV_EN_EP0_OUT_ACK_IRQEN |
		VHUB_DEV_EN_EP0_SETUP_IRQEN;
	if (d->gadget.speed == USB_SPEED_HIGH)
		reg |= VHUB_DEV_EN_SPEED_SEL_HIGH;
	writel(reg, d->regs + AST_VHUB_DEV_EN_CTRL);

	/* Enable device interrupt in the hub as well */
	hmsk = VHUB_IRQ_DEVICE1 << d->index;
	reg = readl(d->vhub->regs + AST_VHUB_IER);
	reg |= hmsk;
	writel(reg, d->vhub->regs + AST_VHUB_IER);

	/* Set EP0 DMA buffer address */
	writel(d->ep0.buf_dma, d->regs + AST_VHUB_DEV_EP0_DATA);

	/* Clear stall on all EPs */
	for (i = 0; i < AST_VHUB_NUM_GEN_EPs; i++) {
		struct ast_vhub_ep *ep = d->epns[i];

		if (ep && (ep->epn.stalled || ep->epn.wedged)) {
			ep->epn.stalled = false;
			ep->epn.wedged = false;
			ast_vhub_update_epn_stall(ep);
		}
	}

	/* Additional cleanups */
	d->wakeup_en = false;
	d->enabled = true;
}