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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3 {int connected; scalar_t__ revision; int test_mode; int /*<<< orphan*/  regs; scalar_t__ setup_packet_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DCFG ; 
 int /*<<< orphan*/  DWC3_DCFG_DEVADDR_MASK ; 
 int /*<<< orphan*/  DWC3_DCTL ; 
 int /*<<< orphan*/  DWC3_DCTL_TSTCTRL_MASK ; 
 scalar_t__ DWC3_REVISION_188A ; 
 int /*<<< orphan*/  dwc3_clear_stall_all_ep (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_gadget_disconnect_interrupt (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc3_reset_gadget (struct dwc3*) ; 
 int /*<<< orphan*/  dwc3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_gadget_reset_interrupt(struct dwc3 *dwc)
{
	u32			reg;

	dwc->connected = true;

	/*
	 * WORKAROUND: DWC3 revisions <1.88a have an issue which
	 * would cause a missing Disconnect Event if there's a
	 * pending Setup Packet in the FIFO.
	 *
	 * There's no suggested workaround on the official Bug
	 * report, which states that "unless the driver/application
	 * is doing any special handling of a disconnect event,
	 * there is no functional issue".
	 *
	 * Unfortunately, it turns out that we _do_ some special
	 * handling of a disconnect event, namely complete all
	 * pending transfers, notify gadget driver of the
	 * disconnection, and so on.
	 *
	 * Our suggested workaround is to follow the Disconnect
	 * Event steps here, instead, based on a setup_packet_pending
	 * flag. Such flag gets set whenever we have a SETUP_PENDING
	 * status for EP0 TRBs and gets cleared on XferComplete for the
	 * same endpoint.
	 *
	 * Refers to:
	 *
	 * STAR#9000466709: RTL: Device : Disconnect event not
	 * generated if setup packet pending in FIFO
	 */
	if (dwc->revision < DWC3_REVISION_188A) {
		if (dwc->setup_packet_pending)
			dwc3_gadget_disconnect_interrupt(dwc);
	}

	dwc3_reset_gadget(dwc);

	reg = dwc3_readl(dwc->regs, DWC3_DCTL);
	reg &= ~DWC3_DCTL_TSTCTRL_MASK;
	dwc3_writel(dwc->regs, DWC3_DCTL, reg);
	dwc->test_mode = false;
	dwc3_clear_stall_all_ep(dwc);

	/* Reset device address to zero */
	reg = dwc3_readl(dwc->regs, DWC3_DCFG);
	reg &= ~(DWC3_DCFG_DEVADDR_MASK);
	dwc3_writel(dwc->regs, DWC3_DCFG, reg);
}