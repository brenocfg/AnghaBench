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
typedef  int u16 ;
struct usb_ctrlrequest {int bRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct ast_vhub_ep {int dummy; } ;
typedef  enum std_req_rc { ____Placeholder_std_req_rc } std_req_rc ;

/* Variables and functions */
 int C_HUB_LOCAL_POWER ; 
 int C_HUB_OVER_CURRENT ; 
#define  ClearHubFeature 138 
#define  ClearPortFeature 137 
#define  ClearTTBuffer 136 
 int /*<<< orphan*/  EPDBG (struct ast_vhub_ep*,char*,...) ; 
#define  GetHubDescriptor 135 
#define  GetHubStatus 134 
#define  GetPortStatus 133 
#define  GetTTState 132 
#define  ResetTT 131 
#define  SetHubFeature 130 
#define  SetPortFeature 129 
#define  StopTT 128 
 int USB_DT_HUB ; 
 int ast_vhub_clr_port_feature (struct ast_vhub_ep*,int,int) ; 
 int ast_vhub_get_port_stat (struct ast_vhub_ep*,int) ; 
 int ast_vhub_rep_desc (struct ast_vhub_ep*,int,int) ; 
 int ast_vhub_set_port_feature (struct ast_vhub_ep*,int,int) ; 
 int ast_vhub_simple_reply (struct ast_vhub_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int std_req_complete ; 
 int std_req_stall ; 

enum std_req_rc ast_vhub_class_hub_request(struct ast_vhub_ep *ep,
					   struct usb_ctrlrequest *crq)
{
	u16 wValue, wIndex, wLength;

	wValue = le16_to_cpu(crq->wValue);
	wIndex = le16_to_cpu(crq->wIndex);
	wLength = le16_to_cpu(crq->wLength);

	switch ((crq->bRequestType << 8) | crq->bRequest) {
	case GetHubStatus:
		EPDBG(ep, "GetHubStatus\n");
		return ast_vhub_simple_reply(ep, 0, 0, 0, 0);
	case GetPortStatus:
		EPDBG(ep, "GetPortStatus(%d)\n", wIndex & 0xff);
		return ast_vhub_get_port_stat(ep, wIndex & 0xf);
	case GetHubDescriptor:
		if (wValue != (USB_DT_HUB << 8))
			return std_req_stall;
		EPDBG(ep, "GetHubDescriptor(%d)\n", wIndex & 0xff);
		return ast_vhub_rep_desc(ep, USB_DT_HUB, wLength);
	case SetHubFeature:
	case ClearHubFeature:
		EPDBG(ep, "Get/SetHubFeature(%d)\n", wValue);
		/* No feature, just complete the requests */
		if (wValue == C_HUB_LOCAL_POWER ||
		    wValue == C_HUB_OVER_CURRENT)
			return std_req_complete;
		return std_req_stall;
	case SetPortFeature:
		EPDBG(ep, "SetPortFeature(%d,%d)\n", wIndex & 0xf, wValue);
		return ast_vhub_set_port_feature(ep, wIndex & 0xf, wValue);
	case ClearPortFeature:
		EPDBG(ep, "ClearPortFeature(%d,%d)\n", wIndex & 0xf, wValue);
		return ast_vhub_clr_port_feature(ep, wIndex & 0xf, wValue);
	case ClearTTBuffer:
	case ResetTT:
	case StopTT:
		return std_req_complete;
	case GetTTState:
		return ast_vhub_simple_reply(ep, 0, 0, 0, 0);
	default:
		EPDBG(ep, "Unknown class request\n");
	}
	return std_req_stall;
}