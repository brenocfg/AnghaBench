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
struct xhci_slot_ctx {int /*<<< orphan*/  dev_state; int /*<<< orphan*/  tt_info; int /*<<< orphan*/  dev_info2; int /*<<< orphan*/  dev_info; } ;
struct xhci_hcd {int dummy; } ;
struct seq_file {struct xhci_slot_priv* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct xhci_hcd* hcd_to_xhci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_decode_slot_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,TYPE_2__*) ; 

__attribute__((used)) static int xhci_slot_context_show(struct seq_file *s, void *unused)
{
	struct xhci_hcd		*xhci;
	struct xhci_slot_ctx	*slot_ctx;
	struct xhci_slot_priv	*priv = s->private;
	struct xhci_virt_device	*dev = priv->dev;

	xhci = hcd_to_xhci(bus_to_hcd(dev->udev->bus));
	slot_ctx = xhci_get_slot_ctx(xhci, dev->out_ctx);
	seq_printf(s, "%pad: %s\n", &dev->out_ctx->dma,
		   xhci_decode_slot_context(le32_to_cpu(slot_ctx->dev_info),
					    le32_to_cpu(slot_ctx->dev_info2),
					    le32_to_cpu(slot_ctx->tt_info),
					    le32_to_cpu(slot_ctx->dev_state)));

	return 0;
}