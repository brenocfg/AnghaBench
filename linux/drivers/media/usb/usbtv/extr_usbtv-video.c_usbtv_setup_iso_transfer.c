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
struct usbtv {int iso_size; int /*<<< orphan*/  udev; } ;
struct urb {int interval; int number_of_packets; int transfer_buffer_length; TYPE_1__* iso_frame_desc; int /*<<< orphan*/  complete; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  pipe; struct usbtv* context; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int offset; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_ISO_ASAP ; 
 int USBTV_ISOC_PACKETS ; 
 int /*<<< orphan*/  USBTV_VIDEO_ENDP ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvisocpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbtv_iso_cb ; 

__attribute__((used)) static struct urb *usbtv_setup_iso_transfer(struct usbtv *usbtv)
{
	struct urb *ip;
	int size = usbtv->iso_size;
	int i;

	ip = usb_alloc_urb(USBTV_ISOC_PACKETS, GFP_KERNEL);
	if (ip == NULL)
		return NULL;

	ip->dev = usbtv->udev;
	ip->context = usbtv;
	ip->pipe = usb_rcvisocpipe(usbtv->udev, USBTV_VIDEO_ENDP);
	ip->interval = 1;
	ip->transfer_flags = URB_ISO_ASAP;
	ip->transfer_buffer = kcalloc(USBTV_ISOC_PACKETS, size,
						GFP_KERNEL);
	if (!ip->transfer_buffer) {
		usb_free_urb(ip);
		return NULL;
	}
	ip->complete = usbtv_iso_cb;
	ip->number_of_packets = USBTV_ISOC_PACKETS;
	ip->transfer_buffer_length = size * USBTV_ISOC_PACKETS;
	for (i = 0; i < USBTV_ISOC_PACKETS; i++) {
		ip->iso_frame_desc[i].offset = size * i;
		ip->iso_frame_desc[i].length = size;
	}

	return ip;
}