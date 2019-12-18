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
typedef  int u32 ;
struct rt2x00_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT_FIRMWARE ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int /*<<< orphan*/  USB_MODE_AUTORUN ; 
 int /*<<< orphan*/  USB_VENDOR_REQUEST_IN ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int rt2x00usb_vendor_request (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800usb_autorun_detect(struct rt2x00_dev *rt2x00dev)
{
	__le32 *reg;
	u32 fw_mode;
	int ret;

	reg = kmalloc(sizeof(*reg), GFP_KERNEL);
	if (reg == NULL)
		return -ENOMEM;
	/* cannot use rt2x00usb_register_read here as it uses different
	 * mode (MULTI_READ vs. DEVICE_MODE) and does not pass the
	 * magic value USB_MODE_AUTORUN (0x11) to the device, thus the
	 * returned value would be invalid.
	 */
	ret = rt2x00usb_vendor_request(rt2x00dev, USB_DEVICE_MODE,
				       USB_VENDOR_REQUEST_IN, 0,
				       USB_MODE_AUTORUN, reg, sizeof(*reg),
				       REGISTER_TIMEOUT_FIRMWARE);
	fw_mode = le32_to_cpu(*reg);
	kfree(reg);
	if (ret < 0)
		return ret;

	if ((fw_mode & 0x00000003) == 2)
		return 1;

	return 0;
}