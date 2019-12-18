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
struct es2_ap_dev {int /*<<< orphan*/  apb_log_fifo; int /*<<< orphan*/  usb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  APB1_LOG_MSG_SIZE ; 
 int /*<<< orphan*/  ES2_USB_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  GB_APB_REQUEST_LOG ; 
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  kfifo_in (int /*<<< orphan*/ *,char*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apb_log_get(struct es2_ap_dev *es2, char *buf)
{
	int retval;

	do {
		retval = usb_control_msg(es2->usb_dev,
					 usb_rcvctrlpipe(es2->usb_dev, 0),
					 GB_APB_REQUEST_LOG,
					 USB_DIR_IN | USB_TYPE_VENDOR |
					 USB_RECIP_INTERFACE,
					 0x00, 0x00,
					 buf,
					 APB1_LOG_MSG_SIZE,
					 ES2_USB_CTRL_TIMEOUT);
		if (retval > 0)
			kfifo_in(&es2->apb_log_fifo, buf, retval);
	} while (retval > 0);
}