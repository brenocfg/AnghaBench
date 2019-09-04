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
struct mcba_usb_msg_fw_ver {int /*<<< orphan*/  pic; int /*<<< orphan*/  cmd_id; } ;
struct mcba_usb_msg {int dummy; } ;
struct mcba_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBCA_CMD_READ_FW_VERSION ; 
 int /*<<< orphan*/  mcba_usb_xmit_cmd (struct mcba_priv*,struct mcba_usb_msg*) ; 

__attribute__((used)) static void mcba_usb_xmit_read_fw_ver(struct mcba_priv *priv, u8 pic)
{
	struct mcba_usb_msg_fw_ver usb_msg = {
		.cmd_id = MBCA_CMD_READ_FW_VERSION,
		.pic = pic
	};

	mcba_usb_xmit_cmd(priv, (struct mcba_usb_msg *)&usb_msg);
}