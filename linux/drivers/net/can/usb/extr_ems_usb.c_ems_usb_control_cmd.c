#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ems_usb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * generic; } ;
struct ems_cpc_msg {TYPE_1__ msg; scalar_t__ msgid; scalar_t__ length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_CMD_TYPE_CONTROL ; 
 scalar_t__ CPC_MSG_HEADER_LEN ; 
 int ems_usb_command_msg (struct ems_usb*,struct ems_cpc_msg*) ; 

__attribute__((used)) static int ems_usb_control_cmd(struct ems_usb *dev, u8 val)
{
	struct ems_cpc_msg cmd;

	cmd.type = CPC_CMD_TYPE_CONTROL;
	cmd.length = CPC_MSG_HEADER_LEN + 1;

	cmd.msgid = 0;

	cmd.msg.generic[0] = val;

	return ems_usb_command_msg(dev, &cmd);
}