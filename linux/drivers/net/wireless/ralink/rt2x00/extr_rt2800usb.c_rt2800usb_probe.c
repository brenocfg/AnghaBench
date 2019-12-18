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
struct usb_interface {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2800usb_ops ; 
 int rt2x00usb_probe (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rt2800usb_probe(struct usb_interface *usb_intf,
			   const struct usb_device_id *id)
{
	return rt2x00usb_probe(usb_intf, &rt2800usb_ops);
}