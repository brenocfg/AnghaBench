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
struct esd_usb2 {int net_count; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct esd_usb2* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t show_nets(struct device *d,
			 struct device_attribute *attr, char *buf)
{
	struct usb_interface *intf = to_usb_interface(d);
	struct esd_usb2 *dev = usb_get_intfdata(intf);

	return sprintf(buf, "%d", dev->net_count);
}