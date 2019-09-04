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
struct usb_data_stream {int urbs_initialized; int /*<<< orphan*/  urbs_submitted; int /*<<< orphan*/ * urb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  deb_ts (char*,int) ; 
 int /*<<< orphan*/  err (char*,int) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_urb_kill (struct usb_data_stream*) ; 

int usb_urb_submit(struct usb_data_stream *stream)
{
	int i,ret;
	for (i = 0; i < stream->urbs_initialized; i++) {
		deb_ts("submitting URB no. %d\n",i);
		if ((ret = usb_submit_urb(stream->urb_list[i],GFP_ATOMIC))) {
			err("could not submit URB no. %d - get them all back",i);
			usb_urb_kill(stream);
			return ret;
		}
		stream->urbs_submitted++;
	}
	return 0;
}