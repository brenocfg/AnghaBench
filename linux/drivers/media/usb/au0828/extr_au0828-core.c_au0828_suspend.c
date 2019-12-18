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
struct au0828_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  au0828_dvb_suspend (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_rc_suspend (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_v4l2_suspend (struct au0828_dev*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct au0828_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int au0828_suspend(struct usb_interface *interface,
				pm_message_t message)
{
	struct au0828_dev *dev = usb_get_intfdata(interface);

	if (!dev)
		return 0;

	pr_info("Suspend\n");

	au0828_rc_suspend(dev);
	au0828_v4l2_suspend(dev);
	au0828_dvb_suspend(dev);

	/* FIXME: should suspend also ATV/DTV */

	return 0;
}