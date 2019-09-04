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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S2255_CONFIG_EP ; 
 long usb_bulk_msg (struct usb_device*,int,unsigned char*,int,int*,int) ; 
 int usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s2255_write_config(struct usb_device *udev, unsigned char *pbuf,
			      int size)
{
	int pipe;
	int done;
	long retval = -1;
	if (udev) {
		pipe = usb_sndbulkpipe(udev, S2255_CONFIG_EP);
		retval = usb_bulk_msg(udev, pipe, pbuf, size, &done, 500);
	}
	return retval;
}