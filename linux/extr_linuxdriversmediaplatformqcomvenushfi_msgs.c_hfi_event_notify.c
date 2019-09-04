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
struct venus_inst {int dummy; } ;
struct venus_core {int dummy; } ;
struct hfi_msg_event_notify_pkt {int event_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_SYS_ERROR ; 
#define  HFI_EVENT_RELEASE_BUFFER_REFERENCE 132 
#define  HFI_EVENT_SESSION_ERROR 131 
#define  HFI_EVENT_SESSION_PROPERTY_CHANGED 130 
#define  HFI_EVENT_SESSION_SEQUENCE_CHANGED 129 
#define  HFI_EVENT_SYS_ERROR 128 
 int /*<<< orphan*/  event_release_buffer_ref (struct venus_core*,struct venus_inst*,struct hfi_msg_event_notify_pkt*) ; 
 int /*<<< orphan*/  event_seq_changed (struct venus_core*,struct venus_inst*,struct hfi_msg_event_notify_pkt*) ; 
 int /*<<< orphan*/  event_session_error (struct venus_core*,struct venus_inst*,struct hfi_msg_event_notify_pkt*) ; 
 int /*<<< orphan*/  event_sys_error (struct venus_core*,int /*<<< orphan*/ ,struct hfi_msg_event_notify_pkt*) ; 

__attribute__((used)) static void hfi_event_notify(struct venus_core *core, struct venus_inst *inst,
			     void *packet)
{
	struct hfi_msg_event_notify_pkt *pkt = packet;

	if (!packet)
		return;

	switch (pkt->event_id) {
	case HFI_EVENT_SYS_ERROR:
		event_sys_error(core, EVT_SYS_ERROR, pkt);
		break;
	case HFI_EVENT_SESSION_ERROR:
		event_session_error(core, inst, pkt);
		break;
	case HFI_EVENT_SESSION_SEQUENCE_CHANGED:
		event_seq_changed(core, inst, pkt);
		break;
	case HFI_EVENT_RELEASE_BUFFER_REFERENCE:
		event_release_buffer_ref(core, inst, pkt);
		break;
	case HFI_EVENT_SESSION_PROPERTY_CHANGED:
		break;
	default:
		break;
	}
}