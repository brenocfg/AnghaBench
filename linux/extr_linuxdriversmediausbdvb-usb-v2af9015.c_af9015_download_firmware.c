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
typedef  scalar_t__ u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct req_t {int addr; scalar_t__ data_len; int /*<<< orphan*/  cmd; int /*<<< orphan*/ * data; int /*<<< orphan*/ * member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct firmware {int size; scalar_t__* data; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct af9015_state {int firmware_size; scalar_t__ firmware_checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT ; 
 scalar_t__ BUF_LEN ; 
 int /*<<< orphan*/  DOWNLOAD_FIRMWARE ; 
 scalar_t__ REQ_HDR_LEN ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ min (scalar_t__,int) ; 

__attribute__((used)) static int af9015_download_firmware(struct dvb_usb_device *d,
				    const struct firmware *firmware)
{
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret, i, rem;
	struct req_t req = {DOWNLOAD_FIRMWARE, 0, 0, 0, 0, 0, NULL};
	u16 checksum;

	dev_dbg(&intf->dev, "\n");

	/* Calc checksum, we need it when copy firmware to slave demod */
	for (i = 0, checksum = 0; i < firmware->size; i++)
		checksum += firmware->data[i];

	state->firmware_size = firmware->size;
	state->firmware_checksum = checksum;

	#define LEN_MAX (BUF_LEN - REQ_HDR_LEN) /* Max payload size */
	for (rem = firmware->size; rem > 0; rem -= LEN_MAX) {
		req.data_len = min(LEN_MAX, rem);
		req.data = (u8 *)&firmware->data[firmware->size - rem];
		req.addr = 0x5100 + firmware->size - rem;
		ret = af9015_ctrl_msg(d, &req);
		if (ret) {
			dev_err(&intf->dev, "firmware download failed %d\n",
				ret);
			goto err;
		}
	}

	req.cmd = BOOT;
	req.data_len = 0;
	ret = af9015_ctrl_msg(d, &req);
	if (ret) {
		dev_err(&intf->dev, "firmware boot failed %d\n", ret);
		goto err;
	}

	return 0;
err:
	dev_dbg(&intf->dev, "failed %d\n", ret);
	return ret;
}