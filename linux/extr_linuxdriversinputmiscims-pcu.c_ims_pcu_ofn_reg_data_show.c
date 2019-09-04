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
typedef  int /*<<< orphan*/  u8 ;
struct usb_interface {int dummy; } ;
struct ims_pcu {int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  ofn_reg_addr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ims_pcu_read_ofn_config (struct ims_pcu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct ims_pcu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t ims_pcu_ofn_reg_data_show(struct device *dev,
					 struct device_attribute *dattr,
					 char *buf)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	int error;
	u8 data;

	mutex_lock(&pcu->cmd_mutex);
	error = ims_pcu_read_ofn_config(pcu, pcu->ofn_reg_addr, &data);
	mutex_unlock(&pcu->cmd_mutex);

	if (error)
		return error;

	return scnprintf(buf, PAGE_SIZE, "%x\n", data);
}