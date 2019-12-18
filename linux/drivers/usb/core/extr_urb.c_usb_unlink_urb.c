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
struct urb {int /*<<< orphan*/  ep; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNRESET ; 
 int EIDRM ; 
 int EINVAL ; 
 int ENODEV ; 
 int usb_hcd_unlink_urb (struct urb*,int /*<<< orphan*/ ) ; 

int usb_unlink_urb(struct urb *urb)
{
	if (!urb)
		return -EINVAL;
	if (!urb->dev)
		return -ENODEV;
	if (!urb->ep)
		return -EIDRM;
	return usb_hcd_unlink_urb(urb, -ECONNRESET);
}