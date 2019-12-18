#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_12__ {scalar_t__ resuming_ports; scalar_t__ suspended_ports; scalar_t__ port_c_suspend; } ;
struct TYPE_13__ {TYPE_5__ bus_state; } ;
struct TYPE_10__ {scalar_t__ resuming_ports; scalar_t__ suspended_ports; scalar_t__ port_c_suspend; } ;
struct TYPE_11__ {TYPE_3__ bus_state; } ;
struct xhci_hcd {int quirks; TYPE_6__ usb3_rhub; TYPE_4__ usb2_rhub; TYPE_2__* op_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  controller; } ;
struct TYPE_14__ {TYPE_1__ self; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int CMD_RESET ; 
 int ENODEV ; 
 int STS_CNR ; 
 int STS_HALT ; 
 int XHCI_ASMEDIA_MODIFY_FLOWCONTROL ; 
 int XHCI_INTEL_HOST ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xhci_dbg_init ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usb_asmedia_modifyflowcontrol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*) ; 
 int xhci_handshake (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* xhci_to_hcd (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

int xhci_reset(struct xhci_hcd *xhci)
{
	u32 command;
	u32 state;
	int ret;

	state = readl(&xhci->op_regs->status);

	if (state == ~(u32)0) {
		xhci_warn(xhci, "Host not accessible, reset failed.\n");
		return -ENODEV;
	}

	if ((state & STS_HALT) == 0) {
		xhci_warn(xhci, "Host controller not halted, aborting reset.\n");
		return 0;
	}

	xhci_dbg_trace(xhci, trace_xhci_dbg_init, "// Reset the HC");
	command = readl(&xhci->op_regs->command);
	command |= CMD_RESET;
	writel(command, &xhci->op_regs->command);

	/* Existing Intel xHCI controllers require a delay of 1 mS,
	 * after setting the CMD_RESET bit, and before accessing any
	 * HC registers. This allows the HC to complete the
	 * reset operation and be ready for HC register access.
	 * Without this delay, the subsequent HC register access,
	 * may result in a system hang very rarely.
	 */
	if (xhci->quirks & XHCI_INTEL_HOST)
		udelay(1000);

	ret = xhci_handshake(&xhci->op_regs->command,
			CMD_RESET, 0, 10 * 1000 * 1000);
	if (ret)
		return ret;

	if (xhci->quirks & XHCI_ASMEDIA_MODIFY_FLOWCONTROL)
		usb_asmedia_modifyflowcontrol(to_pci_dev(xhci_to_hcd(xhci)->self.controller));

	xhci_dbg_trace(xhci, trace_xhci_dbg_init,
			 "Wait for controller to be ready for doorbell rings");
	/*
	 * xHCI cannot write to any doorbells or operational registers other
	 * than status until the "Controller Not Ready" flag is cleared.
	 */
	ret = xhci_handshake(&xhci->op_regs->status,
			STS_CNR, 0, 10 * 1000 * 1000);

	xhci->usb2_rhub.bus_state.port_c_suspend = 0;
	xhci->usb2_rhub.bus_state.suspended_ports = 0;
	xhci->usb2_rhub.bus_state.resuming_ports = 0;
	xhci->usb3_rhub.bus_state.port_c_suspend = 0;
	xhci->usb3_rhub.bus_state.suspended_ports = 0;
	xhci->usb3_rhub.bus_state.resuming_ports = 0;

	return ret;
}