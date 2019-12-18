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
struct venus_inst {TYPE_1__* ops; int /*<<< orphan*/  error; } ;
struct venus_core {int dummy; } ;
struct hfi_msg_event_release_buffer_ref_pkt {int /*<<< orphan*/  output_tag; int /*<<< orphan*/  extradata_buffer; int /*<<< orphan*/  packet_buffer; } ;
struct hfi_msg_event_notify_pkt {scalar_t__ ext_event_data; } ;
struct hfi_event_data {int /*<<< orphan*/  tag; int /*<<< orphan*/  extradata_buffer; int /*<<< orphan*/  packet_buffer; int /*<<< orphan*/  event_type; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* event_notify ) (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_event_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_SYS_EVENT_CHANGE ; 
 int /*<<< orphan*/  HFI_ERR_NONE ; 
 int /*<<< orphan*/  HFI_EVENT_RELEASE_BUFFER_REFERENCE ; 
 int /*<<< orphan*/  stub1 (struct venus_inst*,int /*<<< orphan*/ ,struct hfi_event_data*) ; 

__attribute__((used)) static void event_release_buffer_ref(struct venus_core *core,
				     struct venus_inst *inst,
				     struct hfi_msg_event_notify_pkt *pkt)
{
	struct hfi_event_data event = {0};
	struct hfi_msg_event_release_buffer_ref_pkt *data;

	data = (struct hfi_msg_event_release_buffer_ref_pkt *)
		pkt->ext_event_data;

	event.event_type = HFI_EVENT_RELEASE_BUFFER_REFERENCE;
	event.packet_buffer = data->packet_buffer;
	event.extradata_buffer = data->extradata_buffer;
	event.tag = data->output_tag;

	inst->error = HFI_ERR_NONE;
	inst->ops->event_notify(inst, EVT_SYS_EVENT_CHANGE, &event);
}