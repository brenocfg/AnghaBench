#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ret_unlink; int /*<<< orphan*/  cmd_unlink; int /*<<< orphan*/  ret_submit; int /*<<< orphan*/  cmd_submit; } ;
struct TYPE_4__ {int command; } ;
struct usbip_header {TYPE_1__ u; TYPE_2__ base; } ;
typedef  int __u32 ;

/* Variables and functions */
#define  USBIP_CMD_SUBMIT 131 
#define  USBIP_CMD_UNLINK 130 
#define  USBIP_RET_SUBMIT 129 
#define  USBIP_RET_UNLINK 128 
 int /*<<< orphan*/  correct_endian_basic (TYPE_2__*,int) ; 
 int /*<<< orphan*/  correct_endian_cmd_submit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  correct_endian_cmd_unlink (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  correct_endian_ret_submit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  correct_endian_ret_unlink (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void usbip_header_correct_endian(struct usbip_header *pdu, int send)
{
	__u32 cmd = 0;

	if (send)
		cmd = pdu->base.command;

	correct_endian_basic(&pdu->base, send);

	if (!send)
		cmd = pdu->base.command;

	switch (cmd) {
	case USBIP_CMD_SUBMIT:
		correct_endian_cmd_submit(&pdu->u.cmd_submit, send);
		break;
	case USBIP_RET_SUBMIT:
		correct_endian_ret_submit(&pdu->u.ret_submit, send);
		break;
	case USBIP_CMD_UNLINK:
		correct_endian_cmd_unlink(&pdu->u.cmd_unlink, send);
		break;
	case USBIP_RET_UNLINK:
		correct_endian_ret_unlink(&pdu->u.ret_unlink, send);
		break;
	default:
		/* NOT REACHED */
		pr_err("unknown command\n");
		break;
	}
}