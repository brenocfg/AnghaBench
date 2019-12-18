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
struct us_data {int /*<<< orphan*/  dev_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct us_data* usb_get_intfdata (struct usb_interface*) ; 

int usb_stor_pre_reset(struct usb_interface *iface)
{
	struct us_data *us = usb_get_intfdata(iface);

	/* Make sure no command runs during the reset */
	mutex_lock(&us->dev_mutex);
	return 0;
}