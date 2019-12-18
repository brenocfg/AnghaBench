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
typedef  int u32 ;
typedef  int u16 ;
struct usb_ep {int dummy; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bDescriptorType; } ;
struct TYPE_6__ {int enabled; int is_iso; int stalled; int wedged; int desc_mode; int chunk_max; int descs_dma; int dma_conf; int /*<<< orphan*/  g_idx; scalar_t__ regs; scalar_t__ is_in; scalar_t__ descs; scalar_t__ d_last; scalar_t__ d_next; } ;
struct TYPE_5__ {int maxpacket; } ;
struct ast_vhub_ep {scalar_t__ d_idx; TYPE_3__ epn; TYPE_2__ ep; struct ast_vhub* vhub; struct ast_vhub_dev* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct ast_vhub_dev {scalar_t__ index; TYPE_1__ gadget; int /*<<< orphan*/  driver; } ;
struct ast_vhub {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int AST_VHUB_DESCS_COUNT ; 
 scalar_t__ AST_VHUB_EP_ACK_IER ; 
 scalar_t__ AST_VHUB_EP_ACK_ISR ; 
 scalar_t__ AST_VHUB_EP_CONFIG ; 
 scalar_t__ AST_VHUB_EP_DESC_BASE ; 
 scalar_t__ AST_VHUB_EP_DESC_STATUS ; 
 scalar_t__ AST_VHUB_EP_DMA_CTLSTAT ; 
 scalar_t__ AST_VHUB_EP_TOGGLE ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,...) ; 
 int /*<<< orphan*/  EPVDBG (struct ast_vhub_ep*,char*,int) ; 
 int /*<<< orphan*/  EP_TYPE_BULK ; 
 int /*<<< orphan*/  EP_TYPE_INT ; 
 int /*<<< orphan*/  EP_TYPE_ISO ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  USB_DT_ENDPOINT ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int VHUB_EP_CFG_DIR_OUT ; 
 int VHUB_EP_CFG_ENABLE ; 
 int VHUB_EP_CFG_SET_DEV (scalar_t__) ; 
 int VHUB_EP_CFG_SET_EP_NUM (scalar_t__) ; 
 int VHUB_EP_CFG_SET_MAX_PKT (int) ; 
 int VHUB_EP_CFG_SET_TYPE (int /*<<< orphan*/ ) ; 
 int VHUB_EP_DMA_CTRL_RESET ; 
 int VHUB_EP_DMA_DESC_MODE ; 
 int VHUB_EP_DMA_IN_LONG_MODE ; 
 int VHUB_EP_DMA_SINGLE_STAGE ; 
 int VHUB_EP_IRQ (int /*<<< orphan*/ ) ; 
 int VHUB_EP_TOGGLE_SET_EPNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ast_vhub_ep* to_ast_ep (struct usb_ep*) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor const*) ; 
 int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_num (struct usb_endpoint_descriptor const*) ; 
 int usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_ep_type_string (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_epn_enable(struct usb_ep* u_ep,
			       const struct usb_endpoint_descriptor *desc)
{
	struct ast_vhub_ep *ep = to_ast_ep(u_ep);
	struct ast_vhub_dev *dev;
	struct ast_vhub *vhub;
	u16 maxpacket, type;
	unsigned long flags;
	u32 ep_conf, ep_ier, imask;

	/* Check arguments */
	if (!u_ep || !desc)
		return -EINVAL;

	maxpacket = usb_endpoint_maxp(desc);
	if (!ep->d_idx || !ep->dev ||
	    desc->bDescriptorType != USB_DT_ENDPOINT ||
	    maxpacket == 0 || maxpacket > ep->ep.maxpacket) {
		EPDBG(ep, "Invalid EP enable,d_idx=%d,dev=%p,type=%d,mp=%d/%d\n",
		      ep->d_idx, ep->dev, desc->bDescriptorType,
		      maxpacket, ep->ep.maxpacket);
		return -EINVAL;
	}
	if (ep->d_idx != usb_endpoint_num(desc)) {
		EPDBG(ep, "EP number mismatch !\n");
		return -EINVAL;
	}

	if (ep->epn.enabled) {
		EPDBG(ep, "Already enabled\n");
		return -EBUSY;
	}
	dev = ep->dev;
	vhub = ep->vhub;

	/* Check device state */
	if (!dev->driver) {
		EPDBG(ep, "Bogus device state: driver=%p speed=%d\n",
		       dev->driver, dev->gadget.speed);
		return -ESHUTDOWN;
	}

	/* Grab some info from the descriptor */
	ep->epn.is_in = usb_endpoint_dir_in(desc);
	ep->ep.maxpacket = maxpacket;
	type = usb_endpoint_type(desc);
	ep->epn.d_next = ep->epn.d_last = 0;
	ep->epn.is_iso = false;
	ep->epn.stalled = false;
	ep->epn.wedged = false;

	EPDBG(ep, "Enabling [%s] %s num %d maxpacket=%d\n",
	      ep->epn.is_in ? "in" : "out", usb_ep_type_string(type),
	      usb_endpoint_num(desc), maxpacket);

	/* Can we use DMA descriptor mode ? */
	ep->epn.desc_mode = ep->epn.descs && ep->epn.is_in;
	if (ep->epn.desc_mode)
		memset(ep->epn.descs, 0, 8 * AST_VHUB_DESCS_COUNT);

	/*
	 * Large send function can send up to 8 packets from
	 * one descriptor with a limit of 4095 bytes.
	 */
	ep->epn.chunk_max = ep->ep.maxpacket;
	if (ep->epn.is_in) {
		ep->epn.chunk_max <<= 3;
		while (ep->epn.chunk_max > 4095)
			ep->epn.chunk_max -= ep->ep.maxpacket;
	}

	switch(type) {
	case USB_ENDPOINT_XFER_CONTROL:
		EPDBG(ep, "Only one control endpoint\n");
		return -EINVAL;
	case USB_ENDPOINT_XFER_INT:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_INT);
		break;
	case USB_ENDPOINT_XFER_BULK:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_BULK);
		break;
	case USB_ENDPOINT_XFER_ISOC:
		ep_conf = VHUB_EP_CFG_SET_TYPE(EP_TYPE_ISO);
		ep->epn.is_iso = true;
		break;
	default:
		return -EINVAL;
	}

	/* Encode the rest of the EP config register */
	if (maxpacket < 1024)
		ep_conf |= VHUB_EP_CFG_SET_MAX_PKT(maxpacket);
	if (!ep->epn.is_in)
		ep_conf |= VHUB_EP_CFG_DIR_OUT;
	ep_conf |= VHUB_EP_CFG_SET_EP_NUM(usb_endpoint_num(desc));
	ep_conf |= VHUB_EP_CFG_ENABLE;
	ep_conf |= VHUB_EP_CFG_SET_DEV(dev->index + 1);
	EPVDBG(ep, "config=%08x\n", ep_conf);

	spin_lock_irqsave(&vhub->lock, flags);

	/* Disable HW and reset DMA */
	writel(0, ep->epn.regs + AST_VHUB_EP_CONFIG);
	writel(VHUB_EP_DMA_CTRL_RESET,
	       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

	/* Configure and enable */
	writel(ep_conf, ep->epn.regs + AST_VHUB_EP_CONFIG);

	if (ep->epn.desc_mode) {
		/* Clear DMA status, including the DMA read ptr */
		writel(0, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);

		/* Set descriptor base */
		writel(ep->epn.descs_dma,
		       ep->epn.regs + AST_VHUB_EP_DESC_BASE);

		/* Set base DMA config value */
		ep->epn.dma_conf = VHUB_EP_DMA_DESC_MODE;
		if (ep->epn.is_in)
			ep->epn.dma_conf |= VHUB_EP_DMA_IN_LONG_MODE;

		/* First reset and disable all operations */
		writel(ep->epn.dma_conf | VHUB_EP_DMA_CTRL_RESET,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);

		/* Enable descriptor mode */
		writel(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
	} else {
		/* Set base DMA config value */
		ep->epn.dma_conf = VHUB_EP_DMA_SINGLE_STAGE;

		/* Reset and switch to single stage mode */
		writel(ep->epn.dma_conf | VHUB_EP_DMA_CTRL_RESET,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		writel(ep->epn.dma_conf,
		       ep->epn.regs + AST_VHUB_EP_DMA_CTLSTAT);
		writel(0, ep->epn.regs + AST_VHUB_EP_DESC_STATUS);
	}

	/* Cleanup data toggle just in case */
	writel(VHUB_EP_TOGGLE_SET_EPNUM(ep->epn.g_idx),
	       vhub->regs + AST_VHUB_EP_TOGGLE);

	/* Cleanup and enable ACK interrupt */
	imask = VHUB_EP_IRQ(ep->epn.g_idx);
	writel(imask, vhub->regs + AST_VHUB_EP_ACK_ISR);
	ep_ier = readl(vhub->regs + AST_VHUB_EP_ACK_IER);
	ep_ier |= imask;
	writel(ep_ier, vhub->regs + AST_VHUB_EP_ACK_IER);

	/* Woot, we are online ! */
	ep->epn.enabled = true;

	spin_unlock_irqrestore(&vhub->lock, flags);

	return 0;
}