#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct visor_segment_state {int dummy; } ;
struct visor_device {int /*<<< orphan*/  chipset_dev_no; int /*<<< orphan*/  chipset_bus_no; TYPE_3__* pending_msg_hdr; } ;
struct TYPE_5__ {struct visor_segment_state state; int /*<<< orphan*/  dev_no; int /*<<< orphan*/  bus_no; } ;
struct TYPE_6__ {TYPE_1__ device_change_state; } ;
struct controlvm_message {TYPE_2__ cmd; } ;
typedef  enum controlvm_id { ____Placeholder_controlvm_id } controlvm_id ;
struct TYPE_8__ {int /*<<< orphan*/  controlvm_channel; } ;
struct TYPE_7__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLVM_QUEUE_REQUEST ; 
 int EINVAL ; 
 TYPE_4__* chipset_dev ; 
 int /*<<< orphan*/  controlvm_init_response (struct controlvm_message*,TYPE_3__*,int) ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct controlvm_message*) ; 

__attribute__((used)) static int device_changestate_responder(enum controlvm_id cmd_id,
					struct visor_device *p, int response,
					struct visor_segment_state state)
{
	struct controlvm_message outmsg;

	if (p->pending_msg_hdr->id != cmd_id)
		return -EINVAL;

	controlvm_init_response(&outmsg, p->pending_msg_hdr, response);
	outmsg.cmd.device_change_state.bus_no = p->chipset_bus_no;
	outmsg.cmd.device_change_state.dev_no = p->chipset_dev_no;
	outmsg.cmd.device_change_state.state = state;
	return visorchannel_signalinsert(chipset_dev->controlvm_channel,
					 CONTROLVM_QUEUE_REQUEST, &outmsg);
}