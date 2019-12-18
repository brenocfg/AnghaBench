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
typedef  unsigned int u32 ;
struct usb_device {unsigned int devnum; scalar_t__ speed; } ;
struct fotg210_iso_stream {int usecs; int highspeed; long bandwidth; int bEndpointAddress; unsigned int interval; unsigned int maxp; struct usb_device* udev; void* buf2; void* buf1; void* buf0; } ;
struct fotg210_hcd {int dummy; } ;

/* Variables and functions */
 int HS_USECS_ISO (unsigned int) ; 
 int NS_TO_US (int /*<<< orphan*/ ) ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_SPEED_FULL ; 
 void* cpu_to_hc32 (struct fotg210_hcd*,unsigned int) ; 
 unsigned int hb_mult (unsigned int) ; 
 unsigned int max_packet (unsigned int) ; 
 int /*<<< orphan*/  usb_calc_bus_time (scalar_t__,int,int,unsigned int) ; 
 unsigned int usb_maxpacket (struct usb_device*,int,int) ; 
 unsigned int usb_pipeendpoint (int) ; 
 scalar_t__ usb_pipein (int) ; 

__attribute__((used)) static void iso_stream_init(struct fotg210_hcd *fotg210,
		struct fotg210_iso_stream *stream, struct usb_device *dev,
		int pipe, unsigned interval)
{
	u32 buf1;
	unsigned epnum, maxp;
	int is_input;
	long bandwidth;
	unsigned multi;

	/*
	 * this might be a "high bandwidth" highspeed endpoint,
	 * as encoded in the ep descriptor's wMaxPacket field
	 */
	epnum = usb_pipeendpoint(pipe);
	is_input = usb_pipein(pipe) ? USB_DIR_IN : 0;
	maxp = usb_maxpacket(dev, pipe, !is_input);
	if (is_input)
		buf1 = (1 << 11);
	else
		buf1 = 0;

	maxp = max_packet(maxp);
	multi = hb_mult(maxp);
	buf1 |= maxp;
	maxp *= multi;

	stream->buf0 = cpu_to_hc32(fotg210, (epnum << 8) | dev->devnum);
	stream->buf1 = cpu_to_hc32(fotg210, buf1);
	stream->buf2 = cpu_to_hc32(fotg210, multi);

	/* usbfs wants to report the average usecs per frame tied up
	 * when transfers on this endpoint are scheduled ...
	 */
	if (dev->speed == USB_SPEED_FULL) {
		interval <<= 3;
		stream->usecs = NS_TO_US(usb_calc_bus_time(dev->speed,
				is_input, 1, maxp));
		stream->usecs /= 8;
	} else {
		stream->highspeed = 1;
		stream->usecs = HS_USECS_ISO(maxp);
	}
	bandwidth = stream->usecs * 8;
	bandwidth /= interval;

	stream->bandwidth = bandwidth;
	stream->udev = dev;
	stream->bEndpointAddress = is_input | epnum;
	stream->interval = interval;
	stream->maxp = maxp;
}