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
struct usb_endpoint_descriptor {int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device {scalar_t__ speed; } ;

/* Variables and functions */
 scalar_t__ USB_SPEED_HIGH ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em28xx_audio_ep_packet_size(struct usb_device *udev,
				       struct usb_endpoint_descriptor *e)
{
	int size = le16_to_cpu(e->wMaxPacketSize);

	if (udev->speed == USB_SPEED_HIGH)
		return (size & 0x7ff) *  (1 + (((size) >> 11) & 0x03));

	return size & 0x7ff;
}