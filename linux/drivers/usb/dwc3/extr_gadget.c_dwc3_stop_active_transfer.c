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
struct dwc3_gadget_ep_cmd_params {int dummy; } ;
struct dwc3_ep {int flags; scalar_t__ resource_index; struct dwc3* dwc; } ;
struct dwc3 {scalar_t__ revision; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD_CMDIOC ; 
 int /*<<< orphan*/  DWC3_DEPCMD_ENDTRANSFER ; 
 int /*<<< orphan*/  DWC3_DEPCMD_HIPRI_FORCERM ; 
 int /*<<< orphan*/  DWC3_DEPCMD_PARAM (scalar_t__) ; 
 int DWC3_EP_TRANSFER_STARTED ; 
 scalar_t__ DWC3_REVISION_310A ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ dwc3_is_usb31 (struct dwc3*) ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dwc3_stop_active_transfer(struct dwc3_ep *dep, bool force,
	bool interrupt)
{
	struct dwc3 *dwc = dep->dwc;
	struct dwc3_gadget_ep_cmd_params params;
	u32 cmd;
	int ret;

	if (!(dep->flags & DWC3_EP_TRANSFER_STARTED))
		return;

	/*
	 * NOTICE: We are violating what the Databook says about the
	 * EndTransfer command. Ideally we would _always_ wait for the
	 * EndTransfer Command Completion IRQ, but that's causing too
	 * much trouble synchronizing between us and gadget driver.
	 *
	 * We have discussed this with the IP Provider and it was
	 * suggested to giveback all requests here, but give HW some
	 * extra time to synchronize with the interconnect. We're using
	 * an arbitrary 100us delay for that.
	 *
	 * Note also that a similar handling was tested by Synopsys
	 * (thanks a lot Paul) and nothing bad has come out of it.
	 * In short, what we're doing is:
	 *
	 * - Issue EndTransfer WITH CMDIOC bit set
	 * - Wait 100us
	 *
	 * As of IP version 3.10a of the DWC_usb3 IP, the controller
	 * supports a mode to work around the above limitation. The
	 * software can poll the CMDACT bit in the DEPCMD register
	 * after issuing a EndTransfer command. This mode is enabled
	 * by writing GUCTL2[14]. This polling is already done in the
	 * dwc3_send_gadget_ep_cmd() function so if the mode is
	 * enabled, the EndTransfer command will have completed upon
	 * returning from this function and we don't need to delay for
	 * 100us.
	 *
	 * This mode is NOT available on the DWC_usb31 IP.
	 */

	cmd = DWC3_DEPCMD_ENDTRANSFER;
	cmd |= force ? DWC3_DEPCMD_HIPRI_FORCERM : 0;
	cmd |= interrupt ? DWC3_DEPCMD_CMDIOC : 0;
	cmd |= DWC3_DEPCMD_PARAM(dep->resource_index);
	memset(&params, 0, sizeof(params));
	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	WARN_ON_ONCE(ret);
	dep->resource_index = 0;

	if (dwc3_is_usb31(dwc) || dwc->revision < DWC3_REVISION_310A)
		udelay(100);
}