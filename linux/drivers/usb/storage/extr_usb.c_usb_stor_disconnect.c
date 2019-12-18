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
struct us_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  quiesce_and_remove_host (struct us_data*) ; 
 int /*<<< orphan*/  release_everything (struct us_data*) ; 
 struct us_data* usb_get_intfdata (struct usb_interface*) ; 

void usb_stor_disconnect(struct usb_interface *intf)
{
	struct us_data *us = usb_get_intfdata(intf);

	quiesce_and_remove_host(us);
	release_everything(us);
}