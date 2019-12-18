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
typedef  int u8 ;
struct usb_interface {int dummy; } ;
struct ims_pcu {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCU_RESET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int ims_pcu_execute_command (struct ims_pcu*,int /*<<< orphan*/ ,int const*,int) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct ims_pcu* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t ims_pcu_reset_device(struct device *dev,
				    struct device_attribute *dattr,
				    const char *buf, size_t count)
{
	static const u8 reset_byte = 1;
	struct usb_interface *intf = to_usb_interface(dev);
	struct ims_pcu *pcu = usb_get_intfdata(intf);
	int value;
	int error;

	error = kstrtoint(buf, 0, &value);
	if (error)
		return error;

	if (value != 1)
		return -EINVAL;

	dev_info(pcu->dev, "Attempting to reset device\n");

	error = ims_pcu_execute_command(pcu, PCU_RESET, &reset_byte, 1);
	if (error) {
		dev_info(pcu->dev,
			 "Failed to reset device, error: %d\n",
			 error);
		return error;
	}

	return count;
}