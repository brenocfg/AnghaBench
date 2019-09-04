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
struct usb_usbvision {scalar_t__ streaming; int /*<<< orphan*/  wait_stream; } ;

/* Variables and functions */
 int USBVISION_NUMSBUF ; 
 int USBVISION_URB_FRAMES ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 scalar_t__ stream_idle ; 
 scalar_t__ stream_interrupt ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int usbvision_stream_interrupt(struct usb_usbvision *usbvision)
{
	int ret = 0;

	/* stop reading from the device */

	usbvision->streaming = stream_interrupt;
	ret = wait_event_timeout(usbvision->wait_stream,
				 (usbvision->streaming == stream_idle),
				 msecs_to_jiffies(USBVISION_NUMSBUF*USBVISION_URB_FRAMES));
	return ret;
}