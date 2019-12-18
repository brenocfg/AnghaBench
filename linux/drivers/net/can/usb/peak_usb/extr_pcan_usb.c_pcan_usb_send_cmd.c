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
typedef  void* u8 ;
struct peak_usb_device {int state; int /*<<< orphan*/  netdev; void** cmd_buf; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int PCAN_USB_CMD_ARGS ; 
 int /*<<< orphan*/  PCAN_USB_CMD_ARGS_LEN ; 
 size_t PCAN_USB_CMD_FUNC ; 
 int /*<<< orphan*/  PCAN_USB_CMD_LEN ; 
 size_t PCAN_USB_CMD_NUM ; 
 int /*<<< orphan*/  PCAN_USB_COMMAND_TIMEOUT ; 
 int /*<<< orphan*/  PCAN_USB_EP_CMDOUT ; 
 int PCAN_USB_STATE_CONNECTED ; 
 int /*<<< orphan*/  memcpy (void**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,void*,void*,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcan_usb_send_cmd(struct peak_usb_device *dev, u8 f, u8 n, u8 *p)
{
	int err;
	int actual_length;

	/* usb device unregistered? */
	if (!(dev->state & PCAN_USB_STATE_CONNECTED))
		return 0;

	dev->cmd_buf[PCAN_USB_CMD_FUNC] = f;
	dev->cmd_buf[PCAN_USB_CMD_NUM] = n;

	if (p)
		memcpy(dev->cmd_buf + PCAN_USB_CMD_ARGS,
			p, PCAN_USB_CMD_ARGS_LEN);

	err = usb_bulk_msg(dev->udev,
			usb_sndbulkpipe(dev->udev, PCAN_USB_EP_CMDOUT),
			dev->cmd_buf, PCAN_USB_CMD_LEN, &actual_length,
			PCAN_USB_COMMAND_TIMEOUT);
	if (err)
		netdev_err(dev->netdev,
			"sending cmd f=0x%x n=0x%x failure: %d\n",
			f, n, err);
	return err;
}