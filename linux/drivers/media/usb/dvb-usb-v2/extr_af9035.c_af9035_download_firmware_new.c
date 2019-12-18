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
struct usb_req {int wlen; int /*<<< orphan*/ * wbuf; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int* data; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FW_SCATTER_WR ; 
 int HDR_SIZE ; 
 int af9035_ctrl_msg (struct dvb_usb_device*,struct usb_req*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int af9035_download_firmware_new(struct dvb_usb_device *d,
		const struct firmware *fw)
{
	struct usb_interface *intf = d->intf;
	int ret, i, i_prev;
	struct usb_req req_fw_dl = { CMD_FW_SCATTER_WR, 0, 0, NULL, 0, NULL };
	#define HDR_SIZE 7

	/*
	 * There seems to be following firmware header. Meaning of bytes 0-3
	 * is unknown.
	 *
	 * 0: 3
	 * 1: 0, 1
	 * 2: 0
	 * 3: 1, 2, 3
	 * 4: addr MSB
	 * 5: addr LSB
	 * 6: count of data bytes ?
	 */
	for (i = HDR_SIZE, i_prev = 0; i <= fw->size; i++) {
		if (i == fw->size ||
				(fw->data[i + 0] == 0x03 &&
				(fw->data[i + 1] == 0x00 ||
				fw->data[i + 1] == 0x01) &&
				fw->data[i + 2] == 0x00)) {
			req_fw_dl.wlen = i - i_prev;
			req_fw_dl.wbuf = (u8 *) &fw->data[i_prev];
			i_prev = i;
			ret = af9035_ctrl_msg(d, &req_fw_dl);
			if (ret < 0)
				goto err;

			dev_dbg(&intf->dev, "data uploaded=%d\n", i);
		}
	}

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}