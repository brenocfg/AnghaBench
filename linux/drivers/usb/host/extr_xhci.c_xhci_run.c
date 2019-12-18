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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct xhci_hcd {int imod_interval; int quirks; TYPE_2__* ir_set; TYPE_1__* op_regs; } ;
struct xhci_command {int dummy; } ;
struct usb_hcd {int uses_new_polling; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  irq_control; int /*<<< orphan*/  erst_dequeue; } ;
struct TYPE_3__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_EIE ; 
 int ENOMEM ; 
 scalar_t__ ERST_PTR_MASK ; 
 int ER_IRQ_ENABLE (int) ; 
 int ER_IRQ_INTERVAL_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRB_NEC_GET_FW ; 
 int /*<<< orphan*/  TRB_TYPE (int /*<<< orphan*/ ) ; 
 int XHCI_NEC_HOST ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xhci_dbg_init ; 
 int /*<<< orphan*/  usb_hcd_is_primary_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 struct xhci_command* xhci_alloc_command (struct xhci_hcd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbc_init (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xhci_debugfs_init (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_free_command (struct xhci_hcd*,struct xhci_command*) ; 
 int xhci_queue_vendor_command (struct xhci_hcd*,struct xhci_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 int xhci_run_finished (struct xhci_hcd*) ; 
 int xhci_try_enable_msi (struct usb_hcd*) ; 

int xhci_run(struct usb_hcd *hcd)
{
	u32 temp;
	u64 temp_64;
	int ret;
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);

	/* Start the xHCI host controller running only after the USB 2.0 roothub
	 * is setup.
	 */

	hcd->uses_new_polling = 1;
	if (!usb_hcd_is_primary_hcd(hcd))
		return xhci_run_finished(xhci);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "xhci_run");

	ret = xhci_try_enable_msi(hcd);
	if (ret)
		return ret;

	temp_64 = xhci_read_64(xhci, &xhci->ir_set->erst_dequeue);
	temp_64 &= ~ERST_PTR_MASK;
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"ERST deq = 64'h%0lx", (long unsigned int) temp_64);

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Set the interrupt modulation register");
	temp = readl(&xhci->ir_set->irq_control);
	temp &= ~ER_IRQ_INTERVAL_MASK;
	temp |= (xhci->imod_interval / 250) & ER_IRQ_INTERVAL_MASK;
	writel(temp, &xhci->ir_set->irq_control);

	/* Set the HCD state before we enable the irqs */
	temp = readl(&xhci->op_regs->command);
	temp |= (CMD_EIE);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Enable interrupts, cmd = 0x%x.", temp);
	writel(temp, &xhci->op_regs->command);

	temp = readl(&xhci->ir_set->irq_pending);
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"// Enabling event ring interrupter %p by writing 0x%x to irq_pending",
			xhci->ir_set, (unsigned int) ER_IRQ_ENABLE(temp));
	writel(ER_IRQ_ENABLE(temp), &xhci->ir_set->irq_pending);

	if (xhci->quirks & XHCI_NEC_HOST) {
		struct xhci_command *command;

		command = xhci_alloc_command(xhci, false, GFP_KERNEL);
		if (!command)
			return -ENOMEM;

		ret = xhci_queue_vendor_command(xhci, command, 0, 0, 0,
				TRB_TYPE(TRB_NEC_GET_FW));
		if (ret)
			xhci_free_command(xhci, command);
	}
	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			"Finished xhci_run for USB2 roothub");

	xhci_dbc_init(xhci);

	xhci_debugfs_init(xhci);

	return 0;
}