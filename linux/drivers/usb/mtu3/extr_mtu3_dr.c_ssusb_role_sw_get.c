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
struct ssusb_mtk {scalar_t__ is_host; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 struct ssusb_mtk* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static enum usb_role ssusb_role_sw_get(struct device *dev)
{
	struct ssusb_mtk *ssusb = dev_get_drvdata(dev);
	enum usb_role role;

	role = ssusb->is_host ? USB_ROLE_HOST : USB_ROLE_DEVICE;

	return role;
}