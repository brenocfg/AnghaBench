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
struct peak_usb_device {int state; scalar_t__ cmd_buf; int /*<<< orphan*/  netdev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 scalar_t__ PCAN_USB_CMD_ARGS ; 
 int /*<<< orphan*/  PCAN_USB_CMD_ARGS_LEN ; 
 int /*<<< orphan*/  PCAN_USB_CMD_LEN ; 
 int /*<<< orphan*/  PCAN_USB_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  PCAN_USB_EP_CMDIN ; 
 int PCAN_USB_STATE_CONNECTED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pcan_usb_send_cmd (struct peak_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_wait_rsp(struct peak_usb_device *dev, u8 f, u8 n, u8 *p)
{
	int err;
	int actual_length;

	/* usb device unregistered? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		return 0;

	/* first, send command */
	err = pcan_usb_send_cmd(dev, f, n, NULL);
	if (err)
		return err;

	err = usb_bulk_msg(dev->udev,
		usb_rcvbulkpipe(dev->udev, PCAN_USB_EP_CMDIN),
		dev->cmd_buf, PCAN_USB_CMD_LEN, &actual_length,
		PCAN_USB_COMMAND_TIMEOUT);
	if (err)
		netdev_err(dev->netdev,
			"waiting rsp f=0x%x n=0x%x failure: %d\n", f, n, err);
	else if (p)
		memcpy(p, dev->cmd_buf + PCAN_USB_CMD_ARGS,
			PCAN_USB_CMD_ARGS_LEN);

	return err;
}