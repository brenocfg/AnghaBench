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
typedef  int u32 ;
struct usb_ctrlrequest {int /*<<< orphan*/  wValue; } ;
struct dwc3 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  USB_INTRF_FUNC_SUSPEND 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_ep0_handle_intf(struct dwc3 *dwc,
		struct usb_ctrlrequest *ctrl, int set)
{
	u32			wValue;
	int			ret = 0;

	wValue = le16_to_cpu(ctrl->wValue);

	switch (wValue) {
	case USB_INTRF_FUNC_SUSPEND:
		/*
		 * REVISIT: Ideally we would enable some low power mode here,
		 * however it's unclear what we should be doing here.
		 *
		 * For now, we're not doing anything, just making sure we return
		 * 0 so USB Command Verifier tests pass without any errors.
		 */
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}