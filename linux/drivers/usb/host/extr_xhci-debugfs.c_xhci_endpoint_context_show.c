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
struct xhci_virt_device {TYPE_2__* out_ctx; TYPE_1__* udev; } ;
struct xhci_slot_priv {struct xhci_virt_device* dev; } ;
struct xhci_hcd {int /*<<< orphan*/  hcc_params; } ;
struct xhci_ep_ctx {int /*<<< orphan*/  tx_info; int /*<<< orphan*/  deq; int /*<<< orphan*/  ep_info2; int /*<<< orphan*/  ep_info; } ;
struct seq_file {struct xhci_slot_priv* private; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int CTX_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_decode_ep_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_ep_ctx* xhci_get_ep_ctx (struct xhci_hcd*,TYPE_2__*,int) ; 

__attribute__((used)) static int xhci_endpoint_context_show(struct seq_file *s, void *unused)
{
	int			dci;
	dma_addr_t		dma;
	struct xhci_hcd		*xhci;
	struct xhci_ep_ctx	*ep_ctx;
	struct xhci_slot_priv	*priv = s->private;
	struct xhci_virt_device	*dev = priv->dev;

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));

	for (dci = 1; dci < 32; dci++) {
		ep_ctx = xhci_get_ep_ctx(xhci, dev->out_ctx, dci);
		dma = dev->out_ctx->dma + dci * CTX_SIZE(xhci->hcc_params);
		seq_printf(s, "%pad: %s\n", &dma,
			   xhci_decode_ep_context(le32_to_cpu(ep_ctx->ep_info),
						  le32_to_cpu(ep_ctx->ep_info2),
						  le64_to_cpu(ep_ctx->deq),
						  le32_to_cpu(ep_ctx->tx_info)));
	}

	return 0;
}