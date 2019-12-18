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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_2__ {int num_urb; struct urb** transfer_buffer; struct urb** urb; } ;
struct em28xx {TYPE_1__ adev; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 struct usb_device* interface_to_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_free_coherent (struct usb_device*,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void em28xx_audio_free_urb(struct em28xx *dev)
{
	struct usb_device *udev = interface_to_usbdev(dev->intf);
	int i;

	for (i = 0; i < dev->adev.num_urb; i++) {
		struct urb *urb = dev->adev.urb[i];

		if (!urb)
			continue;

		usb_free_coherent(udev, urb->transfer_buffer_length,
				  dev->adev.transfer_buffer[i],
				  urb->transfer_dma);

		usb_free_urb(urb);
	}
	kfree(dev->adev.urb);
	kfree(dev->adev.transfer_buffer);
	dev->adev.num_urb = 0;
}