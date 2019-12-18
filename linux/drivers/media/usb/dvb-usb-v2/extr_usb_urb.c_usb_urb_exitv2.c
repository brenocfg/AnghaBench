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
struct usb_data_stream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_free_stream_buffers (struct usb_data_stream*) ; 
 int /*<<< orphan*/  usb_urb_free_urbs (struct usb_data_stream*) ; 

int usb_urb_exitv2(struct usb_data_stream *stream)
{
	usb_urb_free_urbs(stream);
	usb_free_stream_buffers(stream);

	return 0;
}