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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_gadget_ep_cmd_params {int dummy; } ;
struct dwc3_ep {scalar_t__ direction; struct dwc3* dwc; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct dwc3 {scalar_t__ revision; TYPE_1__ gadget; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD_CLEARPENDIN ; 
 int /*<<< orphan*/  DWC3_DEPCMD_CLEARSTALL ; 
 scalar_t__ DWC3_REVISION_260A ; 
 scalar_t__ USB_SPEED_SUPER ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dwc3_send_clear_stall_ep_cmd(struct dwc3_ep *dep)
{
	struct dwc3 *dwc = dep->dwc;
	struct dwc3_gadget_ep_cmd_params params;
	u32 cmd = DWC3_DEPCMD_CLEARSTALL;

	/*
	 * As of core revision 2.60a the recommended programming model
	 * is to set the ClearPendIN bit when issuing a Clear Stall EP
	 * command for IN endpoints. This is to prevent an issue where
	 * some (non-compliant) hosts may not send ACK TPs for pending
	 * IN transfers due to a mishandled error condition. Synopsys
	 * STAR 9000614252.
	 */
	if (dep->direction && (dwc->revision >= DWC3_REVISION_260A) &&
	    (dwc->gadget.speed >= USB_SPEED_SUPER))
		cmd |= DWC3_DEPCMD_CLEARPENDIN;

	memset(&params, 0, sizeof(params));

	return dwc3_send_gadget_ep_cmd(dep, cmd, &params);
}