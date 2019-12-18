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
struct dwc3_ep {int /*<<< orphan*/  frame_number; scalar_t__ direction; int /*<<< orphan*/  flags; int /*<<< orphan*/  pending_list; struct dwc3* dwc; } ;
struct TYPE_2__ {scalar_t__ speed; } ;
struct dwc3 {scalar_t__ revision; scalar_t__ version_type; TYPE_1__ gadget; int /*<<< orphan*/  dis_start_transfer_quirk; } ;

/* Variables and functions */
 scalar_t__ DWC31_VERSIONTYPE_EA01 ; 
 scalar_t__ DWC31_VERSIONTYPE_EA06 ; 
 int /*<<< orphan*/  DWC3_ALIGN_FRAME (struct dwc3_ep*,int) ; 
 int /*<<< orphan*/  DWC3_EP_PENDING_REQUEST ; 
 int DWC3_ISOC_MAX_RETRIES ; 
 scalar_t__ DWC3_USB31_REVISION_160A ; 
 scalar_t__ DWC3_USB31_REVISION_170A ; 
 int EAGAIN ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int __dwc3_gadget_kick_transfer (struct dwc3_ep*) ; 
 int dwc3_gadget_start_isoc_quirk (struct dwc3_ep*) ; 
 scalar_t__ dwc3_is_usb31 (struct dwc3*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dwc3_gadget_start_isoc(struct dwc3_ep *dep)
{
	struct dwc3 *dwc = dep->dwc;
	int ret;
	int i;

	if (list_empty(&dep->pending_list)) {
		dep->flags |= DWC3_EP_PENDING_REQUEST;
		return -EAGAIN;
	}

	if (!dwc->dis_start_transfer_quirk && dwc3_is_usb31(dwc) &&
	    (dwc->revision <= DWC3_USB31_REVISION_160A ||
	     (dwc->revision == DWC3_USB31_REVISION_170A &&
	      dwc->version_type >= DWC31_VERSIONTYPE_EA01 &&
	      dwc->version_type <= DWC31_VERSIONTYPE_EA06))) {

		if (dwc->gadget.speed <= USB_SPEED_HIGH && dep->direction)
			return dwc3_gadget_start_isoc_quirk(dep);
	}

	for (i = 0; i < DWC3_ISOC_MAX_RETRIES; i++) {
		dep->frame_number = DWC3_ALIGN_FRAME(dep, i + 1);

		ret = __dwc3_gadget_kick_transfer(dep);
		if (ret != -EAGAIN)
			break;
	}

	return ret;
}