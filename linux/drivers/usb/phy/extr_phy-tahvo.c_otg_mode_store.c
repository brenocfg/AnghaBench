#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* otg; } ;
struct tahvo_usb {scalar_t__ tahvo_mode; int /*<<< orphan*/  serialize; TYPE_2__ phy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {scalar_t__ gadget; scalar_t__ host; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TAHVO_MODE_HOST ; 
 scalar_t__ TAHVO_MODE_PERIPHERAL ; 
 struct tahvo_usb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  tahvo_usb_become_host (struct tahvo_usb*) ; 
 int /*<<< orphan*/  tahvo_usb_become_peripheral (struct tahvo_usb*) ; 
 int /*<<< orphan*/  tahvo_usb_power_off (struct tahvo_usb*) ; 
 int /*<<< orphan*/  tahvo_usb_stop_host (struct tahvo_usb*) ; 
 int /*<<< orphan*/  tahvo_usb_stop_peripheral (struct tahvo_usb*) ; 

__attribute__((used)) static ssize_t otg_mode_store(struct device *device,
			      struct device_attribute *attr,
			      const char *buf, size_t count)
{
	struct tahvo_usb *tu = dev_get_drvdata(device);
	int r;

	mutex_lock(&tu->serialize);
	if (count >= 4 && strncmp(buf, "host", 4) == 0) {
		if (tu->tahvo_mode == TAHVO_MODE_PERIPHERAL)
			tahvo_usb_stop_peripheral(tu);
		tu->tahvo_mode = TAHVO_MODE_HOST;
		if (tu->phy.otg->host) {
			dev_info(device, "HOST mode: host controller present\n");
			tahvo_usb_become_host(tu);
		} else {
			dev_info(device, "HOST mode: no host controller, powering off\n");
			tahvo_usb_power_off(tu);
		}
		r = strlen(buf);
	} else if (count >= 10 && strncmp(buf, "peripheral", 10) == 0) {
		if (tu->tahvo_mode == TAHVO_MODE_HOST)
			tahvo_usb_stop_host(tu);
		tu->tahvo_mode = TAHVO_MODE_PERIPHERAL;
		if (tu->phy.otg->gadget) {
			dev_info(device, "PERIPHERAL mode: gadget driver present\n");
			tahvo_usb_become_peripheral(tu);
		} else {
			dev_info(device, "PERIPHERAL mode: no gadget driver, powering off\n");
			tahvo_usb_power_off(tu);
		}
		r = strlen(buf);
	} else {
		r = -EINVAL;
	}
	mutex_unlock(&tu->serialize);

	return r;
}