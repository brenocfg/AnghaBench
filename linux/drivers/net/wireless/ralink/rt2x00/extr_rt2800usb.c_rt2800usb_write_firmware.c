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
typedef  int u32 ;
struct rt2x00_dev {int /*<<< orphan*/  cap_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_IMAGE_BASE ; 
 int /*<<< orphan*/  H2M_MAILBOX_CID ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  H2M_MAILBOX_STATUS ; 
 int /*<<< orphan*/  REGISTER_TIMEOUT_FIRMWARE ; 
 int /*<<< orphan*/  REQUIRE_FIRMWARE ; 
 int /*<<< orphan*/  RT2860 ; 
 int /*<<< orphan*/  RT2872 ; 
 int /*<<< orphan*/  RT3070 ; 
 int /*<<< orphan*/  USB_DEVICE_MODE ; 
 int /*<<< orphan*/  USB_MODE_FIRMWARE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rt2800usb_autorun_detect (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00_info (struct rt2x00_dev*,char*) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  rt2x00usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2x00usb_vendor_request_sw (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800usb_write_firmware(struct rt2x00_dev *rt2x00dev,
				    const u8 *data, const size_t len)
{
	int status;
	u32 offset;
	u32 length;
	int retval;

	/*
	 * Check which section of the firmware we need.
	 */
	if (rt2x00_rt(rt2x00dev, RT2860) ||
	    rt2x00_rt(rt2x00dev, RT2872) ||
	    rt2x00_rt(rt2x00dev, RT3070)) {
		offset = 0;
		length = 4096;
	} else {
		offset = 4096;
		length = 4096;
	}

	/*
	 * Write firmware to device.
	 */
	retval = rt2800usb_autorun_detect(rt2x00dev);
	if (retval < 0)
		return retval;
	if (retval) {
		rt2x00_info(rt2x00dev,
			    "Firmware loading not required - NIC in AutoRun mode\n");
		__clear_bit(REQUIRE_FIRMWARE, &rt2x00dev->cap_flags);
	} else {
		rt2x00usb_register_multiwrite(rt2x00dev, FIRMWARE_IMAGE_BASE,
					      data + offset, length);
	}

	rt2x00usb_register_write(rt2x00dev, H2M_MAILBOX_CID, ~0);
	rt2x00usb_register_write(rt2x00dev, H2M_MAILBOX_STATUS, ~0);

	/*
	 * Send firmware request to device to load firmware,
	 * we need to specify a long timeout time.
	 */
	status = rt2x00usb_vendor_request_sw(rt2x00dev, USB_DEVICE_MODE,
					     0, USB_MODE_FIRMWARE,
					     REGISTER_TIMEOUT_FIRMWARE);
	if (status < 0) {
		rt2x00_err(rt2x00dev, "Failed to write Firmware to device\n");
		return status;
	}

	msleep(10);
	rt2x00usb_register_write(rt2x00dev, H2M_MAILBOX_CSR, 0);

	return 0;
}