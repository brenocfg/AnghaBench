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
struct rtsx_ucr {int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RTSX_USB_REQ_POLL ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ polling_pipe ; 
 int rtsx_usb_get_status_with_bulk (struct rtsx_ucr*,int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtsx_usb_get_card_status(struct rtsx_ucr *ucr, u16 *status)
{
	int ret;
	u16 *buf;

	if (!status)
		return -EINVAL;

	if (polling_pipe == 0) {
		buf = kzalloc(sizeof(u16), GFP_KERNEL);
		if (!buf)
			return -ENOMEM;

		ret = usb_control_msg(ucr->pusb_dev,
				usb_rcvctrlpipe(ucr->pusb_dev, 0),
				RTSX_USB_REQ_POLL,
				USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0, 0, buf, 2, 100);
		*status = *buf;

		kfree(buf);
	} else {
		ret = rtsx_usb_get_status_with_bulk(ucr, status);
	}

	/* usb_control_msg may return positive when success */
	if (ret < 0)
		return ret;

	return 0;
}