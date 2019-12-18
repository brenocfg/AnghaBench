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
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_driver {int dummy; } ;

/* Variables and functions */
 struct usb_driver* ERR_PTR (int) ; 
 int wdm_create (struct usb_interface*,struct usb_endpoint_descriptor*,int,int (*) (struct usb_interface*,int)) ; 
 struct usb_driver wdm_driver ; 

struct usb_driver *usb_cdc_wdm_register(struct usb_interface *intf,
					struct usb_endpoint_descriptor *ep,
					int bufsize,
					int (*manage_power)(struct usb_interface *, int))
{
	int rv;

	rv = wdm_create(intf, ep, bufsize, manage_power);
	if (rv < 0)
		goto err;

	return &wdm_driver;
err:
	return ERR_PTR(rv);
}