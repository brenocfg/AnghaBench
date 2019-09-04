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
typedef  int /*<<< orphan*/  u16 ;
struct airspy {int* buf; int /*<<< orphan*/  dev; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
#define  CMD_BOARD_ID_READ 137 
#define  CMD_BOARD_PARTID_SERIALNO_READ 136 
#define  CMD_RECEIVER_MODE 135 
#define  CMD_SET_FREQ 134 
#define  CMD_SET_LNA_AGC 133 
#define  CMD_SET_LNA_GAIN 132 
#define  CMD_SET_MIXER_AGC 131 
#define  CMD_SET_MIXER_GAIN 130 
#define  CMD_SET_VGA_GAIN 129 
#define  CMD_VERSION_STRING_READ 128 
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  airspy_dbg_usb_control_msg (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int) ; 
 unsigned int usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int airspy_ctrl_msg(struct airspy *s, u8 request, u16 value, u16 index,
		u8 *data, u16 size)
{
	int ret;
	unsigned int pipe;
	u8 requesttype;

	switch (request) {
	case CMD_RECEIVER_MODE:
	case CMD_SET_FREQ:
		pipe = usb_sndctrlpipe(s->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_DIR_OUT);
		break;
	case CMD_BOARD_ID_READ:
	case CMD_VERSION_STRING_READ:
	case CMD_BOARD_PARTID_SERIALNO_READ:
	case CMD_SET_LNA_GAIN:
	case CMD_SET_MIXER_GAIN:
	case CMD_SET_VGA_GAIN:
	case CMD_SET_LNA_AGC:
	case CMD_SET_MIXER_AGC:
		pipe = usb_rcvctrlpipe(s->udev, 0);
		requesttype = (USB_TYPE_VENDOR | USB_DIR_IN);
		break;
	default:
		dev_err(s->dev, "Unknown command %02x\n", request);
		ret = -EINVAL;
		goto err;
	}

	/* write request */
	if (!(requesttype & USB_DIR_IN))
		memcpy(s->buf, data, size);

	ret = usb_control_msg(s->udev, pipe, request, requesttype, value,
			index, s->buf, size, 1000);
	airspy_dbg_usb_control_msg(s->dev, request, requesttype, value,
			index, s->buf, size);
	if (ret < 0) {
		dev_err(s->dev, "usb_control_msg() failed %d request %02x\n",
				ret, request);
		goto err;
	}

	/* read request */
	if (requesttype & USB_DIR_IN)
		memcpy(data, s->buf, size);

	return 0;
err:
	return ret;
}