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
struct wusbhc {int dummy; } ;
struct whc {TYPE_1__* umc; } ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  PIPE_BULK 131 
#define  PIPE_CONTROL 130 
#define  PIPE_INTERRUPT 129 
#define  PIPE_ISOCHRONOUS 128 
 int asl_urb_enqueue (struct whc*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pzl_urb_enqueue (struct whc*,struct urb*,int /*<<< orphan*/ ) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 
 int usb_pipetype (int /*<<< orphan*/ ) ; 
 struct whc* wusbhc_to_whc (struct wusbhc*) ; 

__attribute__((used)) static int whc_urb_enqueue(struct usb_hcd *usb_hcd, struct urb *urb,
			   gfp_t mem_flags)
{
	struct wusbhc *wusbhc = usb_hcd_to_wusbhc(usb_hcd);
	struct whc *whc = wusbhc_to_whc(wusbhc);
	int ret;

	switch (usb_pipetype(urb->pipe)) {
	case PIPE_INTERRUPT:
		ret = pzl_urb_enqueue(whc, urb, mem_flags);
		break;
	case PIPE_ISOCHRONOUS:
		dev_err(&whc->umc->dev, "isochronous transfers unsupported\n");
		ret = -ENOTSUPP;
		break;
	case PIPE_CONTROL:
	case PIPE_BULK:
	default:
		ret = asl_urb_enqueue(whc, urb, mem_flags);
		break;
	}

	return ret;
}