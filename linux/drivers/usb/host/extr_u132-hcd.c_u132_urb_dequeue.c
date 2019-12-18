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
typedef  size_t u8 ;
struct usb_hcd {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; } ;
struct u132_udev {size_t* endp_number_in; size_t* endp_number_out; } ;
struct u132_endp {int dummy; } ;
struct u132 {int going; struct u132_endp** endp; struct u132_udev* udev; TYPE_2__* addr; TYPE_1__* platform_dev; } ;
struct TYPE_4__ {size_t address; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct u132* hcd_to_u132 (struct usb_hcd*) ; 
 int u132_endp_urb_dequeue (struct u132*,struct u132_endp*,struct urb*,int) ; 
 size_t usb_pipedevice (int /*<<< orphan*/ ) ; 
 size_t usb_pipeendpoint (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_pipein (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u132_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 2) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else {
		u8 usb_addr = usb_pipedevice(urb->pipe);
		u8 usb_endp = usb_pipeendpoint(urb->pipe);
		u8 address = u132->addr[usb_addr].address;
		struct u132_udev *udev = &u132->udev[address];
		if (usb_pipein(urb->pipe)) {
			u8 endp_number = udev->endp_number_in[usb_endp];
			struct u132_endp *endp = u132->endp[endp_number - 1];
			return u132_endp_urb_dequeue(u132, endp, urb, status);
		} else {
			u8 endp_number = udev->endp_number_out[usb_endp];
			struct u132_endp *endp = u132->endp[endp_number - 1];
			return u132_endp_urb_dequeue(u132, endp, urb, status);
		}
	}
}