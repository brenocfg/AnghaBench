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
typedef  int /*<<< orphan*/  u32 ;
struct usb_8dev_priv {int dummy; } ;
struct usb_8dev_cmd_msg {scalar_t__ data; int /*<<< orphan*/  opt2; int /*<<< orphan*/  opt1; int /*<<< orphan*/  command; int /*<<< orphan*/  channel; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  USB_8DEV_GET_SOFTW_HARDW_VER ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ *) ; 
 int usb_8dev_send_cmd (struct usb_8dev_priv*,struct usb_8dev_cmd_msg*,struct usb_8dev_cmd_msg*) ; 

__attribute__((used)) static int usb_8dev_cmd_version(struct usb_8dev_priv *priv, u32 *res)
{
	struct usb_8dev_cmd_msg	inmsg;
	struct usb_8dev_cmd_msg	outmsg = {
		.channel = 0,
		.command = USB_8DEV_GET_SOFTW_HARDW_VER,
		.opt1 = 0,
		.opt2 = 0
	};

	int err = usb_8dev_send_cmd(priv, &outmsg, &inmsg);
	if (err)
		return err;

	*res = be32_to_cpup((__be32 *)inmsg.data);

	return err;
}