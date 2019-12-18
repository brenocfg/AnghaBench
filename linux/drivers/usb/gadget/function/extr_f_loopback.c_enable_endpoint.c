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
struct usb_ep {struct f_loopback* driver_data; } ;
struct usb_composite_dev {int /*<<< orphan*/  gadget; } ;
struct f_loopback {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int config_ep_by_speed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_ep*) ; 
 int usb_ep_enable (struct usb_ep*) ; 

__attribute__((used)) static int enable_endpoint(struct usb_composite_dev *cdev,
			   struct f_loopback *loop, struct usb_ep *ep)
{
	int					result;

	result = config_ep_by_speed(cdev->gadget, &(loop->function), ep);
	if (result)
		goto out;

	result = usb_ep_enable(ep);
	if (result < 0)
		goto out;
	ep->driver_data = loop;
	result = 0;

out:
	return result;
}