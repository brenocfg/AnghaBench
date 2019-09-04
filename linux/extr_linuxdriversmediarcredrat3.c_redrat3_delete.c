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
struct usb_device {int dummy; } ;
struct redrat3_dev {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  bulk_in_buf; TYPE_1__* ep_narrow; int /*<<< orphan*/  learn_urb; int /*<<< orphan*/  flash_urb; int /*<<< orphan*/  wide_urb; int /*<<< orphan*/  narrow_urb; } ;
struct TYPE_2__ {int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct redrat3_dev*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void redrat3_delete(struct redrat3_dev *rr3,
				  struct usb_device *udev)
{
	usb_kill_urb(rr3->narrow_urb);
	usb_kill_urb(rr3->wide_urb);
	usb_kill_urb(rr3->flash_urb);
	usb_kill_urb(rr3->learn_urb);
	usb_free_urb(rr3->narrow_urb);
	usb_free_urb(rr3->wide_urb);
	usb_free_urb(rr3->flash_urb);
	usb_free_urb(rr3->learn_urb);
	usb_free_coherent(udev, le16_to_cpu(rr3->ep_narrow->wMaxPacketSize),
			  rr3->bulk_in_buf, rr3->dma_in);

	kfree(rr3);
}