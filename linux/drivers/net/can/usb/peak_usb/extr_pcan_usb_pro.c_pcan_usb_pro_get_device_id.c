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
struct peak_usb_device {int /*<<< orphan*/  ctrl_idx; int /*<<< orphan*/  cmd_buf; } ;
struct pcan_usb_pro_msg {int dummy; } ;
struct pcan_usb_pro_devid {int /*<<< orphan*/  serial_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAN_USBPRO_GETDEVID ; 
 int /*<<< orphan*/  PCAN_USB_MAX_CMD_LEN ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcan_msg_add_rec (struct pcan_usb_pro_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pcan_msg_init_empty (struct pcan_usb_pro_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pcan_usb_pro_send_cmd (struct peak_usb_device*,struct pcan_usb_pro_msg*) ; 
 int pcan_usb_pro_wait_rsp (struct peak_usb_device*,struct pcan_usb_pro_msg*) ; 

__attribute__((used)) static int pcan_usb_pro_get_device_id(struct peak_usb_device *dev,
				      u32 *device_id)
{
	struct pcan_usb_pro_devid *pdn;
	struct pcan_usb_pro_msg um;
	int err;
	u8 *pc;

	pc = pcan_msg_init_empty(&um, dev->cmd_buf, PCAN_USB_MAX_CMD_LEN);
	pcan_msg_add_rec(&um, PCAN_USBPRO_GETDEVID, dev->ctrl_idx);

	err =  pcan_usb_pro_send_cmd(dev, &um);
	if (err)
		return err;

	err = pcan_usb_pro_wait_rsp(dev, &um);
	if (err)
		return err;

	pdn = (struct pcan_usb_pro_devid *)pc;
	if (device_id)
		*device_id = le32_to_cpu(pdn->serial_num);

	return err;
}