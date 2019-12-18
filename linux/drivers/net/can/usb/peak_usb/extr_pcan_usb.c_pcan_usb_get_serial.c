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
typedef  int /*<<< orphan*/  u32 ;
struct peak_usb_device {int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int PCAN_USB_CMD_ARGS_LEN ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pcan_usb_wait_rsp (struct peak_usb_device*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcan_usb_get_serial(struct peak_usb_device *dev, u32 *serial_number)
{
	u8 args[PCAN_USB_CMD_ARGS_LEN];
	int err;

	err = pcan_usb_wait_rsp(dev, 6, 1, args);
	if (err) {
		netdev_err(dev->netdev, "getting serial failure: %d\n", err);
	} else if (serial_number) {
		__le32 tmp32;

		memcpy(&tmp32, args, 4);
		*serial_number = le32_to_cpu(tmp32);
	}

	return err;
}