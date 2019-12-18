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
struct ssusb_mtk {int is_host; } ;
struct device {int dummy; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int USB_ROLE_HOST ; 
 struct ssusb_mtk* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  ssusb_mode_switch (struct ssusb_mtk*,int) ; 

__attribute__((used)) static int ssusb_role_sw_set(struct device *dev, enum usb_role role)
{
	struct ssusb_mtk *ssusb = dev_get_drvdata(dev);
	bool to_host = false;

	if (role == USB_ROLE_HOST)
		to_host = true;

	if (to_host ^ ssusb->is_host)
		ssusb_mode_switch(ssusb, to_host);

	return 0;
}