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
struct dwc3_gadget_ep_cmd_params {int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; } ;
struct dwc3_ep {int flags; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  ep0_next_event; int /*<<< orphan*/  ep0_trb_addr; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DWC3_DEPCMD_STARTTRANSFER ; 
 int /*<<< orphan*/  DWC3_EP0_COMPLETE ; 
 int DWC3_EP_TRANSFER_STARTED ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int /*<<< orphan*/ ,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_start_trans(struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;
	struct dwc3			*dwc;
	int				ret;

	if (dep->flags & DWC3_EP_TRANSFER_STARTED)
		return 0;

	dwc = dep->dwc;

	memset(&params, 0, sizeof(params));
	params.param0 = upper_32_bits(dwc->ep0_trb_addr);
	params.param1 = lower_32_bits(dwc->ep0_trb_addr);

	ret = dwc3_send_gadget_ep_cmd(dep, DWC3_DEPCMD_STARTTRANSFER, &params);
	if (ret < 0)
		return ret;

	dwc->ep0_next_event = DWC3_EP0_COMPLETE;

	return 0;
}