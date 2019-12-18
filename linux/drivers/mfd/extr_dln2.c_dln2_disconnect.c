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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct dln2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dln2_free (struct dln2_dev*) ; 
 int /*<<< orphan*/  dln2_stop (struct dln2_dev*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 struct dln2_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static void dln2_disconnect(struct usb_interface *interface)
{
	struct dln2_dev *dln2 = usb_get_intfdata(interface);

	dln2_stop(dln2);

	mfd_remove_devices(&interface->dev);

	dln2_free(dln2);
}