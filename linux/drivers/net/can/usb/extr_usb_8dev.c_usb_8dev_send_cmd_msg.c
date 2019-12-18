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
struct usb_8dev_priv {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_8DEV_CMD_TIMEOUT ; 
 int /*<<< orphan*/  USB_8DEV_ENDP_CMD_TX ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_8dev_send_cmd_msg(struct usb_8dev_priv *priv, u8 *msg, int size)
{
	int actual_length;

	return usb_bulk_msg(priv->udev,
			    usb_sndbulkpipe(priv->udev, USB_8DEV_ENDP_CMD_TX),
			    msg, size, &actual_length, USB_8DEV_CMD_TIMEOUT);
}