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

/* Variables and functions */
 int /*<<< orphan*/  REG_600 ; 
 int /*<<< orphan*/  au0828_dvb_resume (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_gpio_setup (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_rc_resume (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_v4l2_resume (struct au0828_dev*) ; 
 int /*<<< orphan*/  au0828_write (struct au0828_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct au0828_dev* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int au0828_resume(struct usb_interface *interface)
{
	struct au0828_dev *dev = usb_get_intfdata(interface);
	if (!dev)
		return 0;

	pr_info("Resume\n");

	/* Power Up the bridge */
	au0828_write(dev, REG_600, 1 << 4);

	/* Bring up the GPIO's and supporting devices */
	au0828_gpio_setup(dev);

	au0828_rc_resume(dev);
	au0828_v4l2_resume(dev);
	au0828_dvb_resume(dev);

	/* FIXME: should resume also ATV/DTV */

	return 0;
}