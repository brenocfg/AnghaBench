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
 int kstrtou8 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct ims_pcu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t ims_pcu_ofn_reg_addr_store(struct device *dev,
					  struct device_attribute *dattr,
					  const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	int error;
	u8 value;

	error = kstrtou8(buf, 0, &value);
	if (error)
		return error;

	mutex_lock(&pcu->cmd_mutex);
	pcu->ofn_reg_addr = value;
	mutex_unlock(&pcu->cmd_mutex);

	return count;
}