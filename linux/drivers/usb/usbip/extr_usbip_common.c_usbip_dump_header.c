#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  error_count; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  actual_length; int /*<<< orphan*/  status; } ;
struct TYPE_9__ {int /*<<< orphan*/  seqnum; } ;
struct TYPE_8__ {int /*<<< orphan*/  interval; int /*<<< orphan*/  number_of_packets; int /*<<< orphan*/  start_frame; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_12__ {TYPE_5__ ret_unlink; TYPE_4__ ret_submit; TYPE_3__ cmd_unlink; TYPE_2__ cmd_submit; } ;
struct TYPE_7__ {int command; int /*<<< orphan*/  ep; int /*<<< orphan*/  direction; int /*<<< orphan*/  devid; int /*<<< orphan*/  seqnum; } ;
struct usbip_header {TYPE_6__ u; TYPE_1__ base; } ;

/* Variables and functions */
#define  USBIP_CMD_SUBMIT 131 
#define  USBIP_CMD_UNLINK 130 
#define  USBIP_RET_SUBMIT 129 
#define  USBIP_RET_UNLINK 128 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void usbip_dump_header(struct usbip_header *pdu)
{
	pr_debug("BASE: cmd %u seq %u devid %u dir %u ep %u\n",
		 pdu->base.command,
		 pdu->base.seqnum,
		 pdu->base.devid,
		 pdu->base.direction,
		 pdu->base.ep);

	switch (pdu->base.command) {
	case USBIP_CMD_SUBMIT:
		pr_debug("USBIP_CMD_SUBMIT: x_flags %u x_len %u sf %u #p %d iv %d\n",
			 pdu->u.cmd_submit.transfer_flags,
			 pdu->u.cmd_submit.transfer_buffer_length,
			 pdu->u.cmd_submit.start_frame,
			 pdu->u.cmd_submit.number_of_packets,
			 pdu->u.cmd_submit.interval);
		break;
	case USBIP_CMD_UNLINK:
		pr_debug("USBIP_CMD_UNLINK: seq %u\n",
			 pdu->u.cmd_unlink.seqnum);
		break;
	case USBIP_RET_SUBMIT:
		pr_debug("USBIP_RET_SUBMIT: st %d al %u sf %d #p %d ec %d\n",
			 pdu->u.ret_submit.status,
			 pdu->u.ret_submit.actual_length,
			 pdu->u.ret_submit.start_frame,
			 pdu->u.ret_submit.number_of_packets,
			 pdu->u.ret_submit.error_count);
		break;
	case USBIP_RET_UNLINK:
		pr_debug("USBIP_RET_UNLINK: status %d\n",
			 pdu->u.ret_unlink.status);
		break;
	default:
		/* NOT REACHED */
		pr_err("unknown command\n");
		break;
	}
}