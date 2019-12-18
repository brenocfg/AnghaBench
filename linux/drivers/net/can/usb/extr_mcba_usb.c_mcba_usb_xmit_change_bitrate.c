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
struct mcba_usb_msg_change_bitrate {int /*<<< orphan*/  bitrate; int /*<<< orphan*/  cmd_id; } ;
struct mcba_usb_msg {int dummy; } ;
struct mcba_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBCA_CMD_CHANGE_BIT_RATE ; 
 int /*<<< orphan*/  mcba_usb_xmit_cmd (struct mcba_priv*,struct mcba_usb_msg*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcba_usb_xmit_change_bitrate(struct mcba_priv *priv, u16 bitrate)
{
	struct mcba_usb_msg_change_bitrate usb_msg = {
		.cmd_id = MBCA_CMD_CHANGE_BIT_RATE
	};

	put_unaligned_be16(bitrate, &usb_msg.bitrate);

	mcba_usb_xmit_cmd(priv, (struct mcba_usb_msg *)&usb_msg);
}