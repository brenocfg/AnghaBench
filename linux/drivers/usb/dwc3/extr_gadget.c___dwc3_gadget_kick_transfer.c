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
typedef  int u32 ;
struct dwc3_trb {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream_id; } ;
struct dwc3_request {struct dwc3_gadget_ep_cmd_params* trb; TYPE_1__ request; int /*<<< orphan*/  trb_dma; } ;
struct dwc3_gadget_ep_cmd_params {int /*<<< orphan*/  param1; int /*<<< orphan*/  param0; } ;
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {int flags; int /*<<< orphan*/  resource_index; int /*<<< orphan*/  frame_number; TYPE_2__ endpoint; scalar_t__ stream_capable; int /*<<< orphan*/  started_list; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int DWC3_DEPCMD_PARAM (int /*<<< orphan*/ ) ; 
 int DWC3_DEPCMD_STARTTRANSFER ; 
 int DWC3_DEPCMD_UPDATETRANSFER ; 
 int DWC3_EP_PENDING_REQUEST ; 
 int DWC3_EP_TRANSFER_STARTED ; 
 int /*<<< orphan*/  dwc3_calc_trbs_left (struct dwc3_ep*) ; 
 int /*<<< orphan*/  dwc3_gadget_del_and_unmap_request (struct dwc3_ep*,struct dwc3_request*,int) ; 
 int /*<<< orphan*/  dwc3_prepare_trbs (struct dwc3_ep*) ; 
 int dwc3_send_gadget_ep_cmd (struct dwc3_ep*,int,struct dwc3_gadget_ep_cmd_params*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dwc3_gadget_ep_cmd_params*,int /*<<< orphan*/ ,int) ; 
 struct dwc3_request* next_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_xfer_isoc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __dwc3_gadget_kick_transfer(struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;
	struct dwc3_request		*req;
	int				starting;
	int				ret;
	u32				cmd;

	if (!dwc3_calc_trbs_left(dep))
		return 0;

	starting = !(dep->flags & DWC3_EP_TRANSFER_STARTED);

	dwc3_prepare_trbs(dep);
	req = next_request(&dep->started_list);
	if (!req) {
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		return 0;
	}

	memset(&params, 0, sizeof(params));

	if (starting) {
		params.param0 = upper_32_bits(req->trb_dma);
		params.param1 = lower_32_bits(req->trb_dma);
		cmd = DWC3_DEPCMD_STARTTRANSFER;

		if (dep->stream_capable)
			cmd |= DWC3_DEPCMD_PARAM(req->request.stream_id);

		if (usb_endpoint_xfer_isoc(dep->endpoint.desc))
			cmd |= DWC3_DEPCMD_PARAM(dep->frame_number);
	} else {
		cmd = DWC3_DEPCMD_UPDATETRANSFER |
			DWC3_DEPCMD_PARAM(dep->resource_index);
	}

	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	if (ret < 0) {
		/*
		 * FIXME we need to iterate over the list of requests
		 * here and stop, unmap, free and del each of the linked
		 * requests instead of what we do now.
		 */
		if (req->trb)
			memset(req->trb, 0, sizeof(struct dwc3_trb));
		dwc3_gadget_del_and_unmap_request(dep, req, ret);
		return ret;
	}

	return 0;
}