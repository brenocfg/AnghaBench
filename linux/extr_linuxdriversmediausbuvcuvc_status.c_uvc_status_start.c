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
struct uvc_device {int /*<<< orphan*/ * int_urb; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int usb_submit_urb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int uvc_status_start(struct uvc_device *dev, gfp_t flags)
{
	if (dev->int_urb == NULL)
		return 0;

	return usb_submit_urb(dev->int_urb, flags);
}