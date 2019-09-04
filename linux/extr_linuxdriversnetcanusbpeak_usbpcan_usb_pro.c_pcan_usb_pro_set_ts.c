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
typedef  int /*<<< orphan*/  u16 ;
struct peak_usb_device {int /*<<< orphan*/  cmd_buf; } ;
struct pcan_usb_pro_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_USBPRO_SETTS ; 
 int /*<<< orphan*/  PCAN_USB_MAX_CMD_LEN ; 
 int /*<<< orphan*/  pcan_msg_add_rec (struct pcan_usb_pro_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_msg_init_empty (struct pcan_usb_pro_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcan_usb_pro_send_cmd (struct peak_usb_device*,struct pcan_usb_pro_msg*) ; 

__attribute__((used)) static int pcan_usb_pro_set_ts(struct peak_usb_device *dev, u16 onoff)
{
	struct pcan_usb_pro_msg um;

	pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_SETTS, onoff);

	return pcan_usb_pro_send_cmd(dev, &um);
}