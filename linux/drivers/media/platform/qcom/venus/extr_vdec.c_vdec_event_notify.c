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
typedef  int u32 ;
struct venus_inst {int session_error; int /*<<< orphan*/  error; struct venus_core* core; } ;
struct venus_core {struct device* dev_dec; } ;
struct hfi_event_data {int /*<<< orphan*/  tag; int /*<<< orphan*/  event_type; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  EVT_SESSION_ERROR 132 
#define  EVT_SYS_EVENT_CHANGE 131 
#define  HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_RESOURCES 130 
#define  HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_RESOURCES 129 
#define  HFI_EVENT_RELEASE_BUFFER_REFERENCE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdec_event_change (struct venus_inst*,struct hfi_event_data*,int) ; 
 int /*<<< orphan*/  venus_helper_release_buf_ref (struct venus_inst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdec_event_notify(struct venus_inst *inst, u32 event,
			      struct hfi_event_data *data)
{
	struct venus_core *core = inst->core;
	struct device *dev = core->dev_dec;

	switch (event) {
	case EVT_SESSION_ERROR:
		inst->session_error = true;
		dev_err(dev, "dec: event session error %x\n", inst->error);
		break;
	case EVT_SYS_EVENT_CHANGE:
		switch (data->event_type) {
		case HFI_EVENT_DATA_SEQUENCE_CHANGED_SUFFICIENT_BUF_RESOURCES:
			vdec_event_change(inst, data, true);
			break;
		case HFI_EVENT_DATA_SEQUENCE_CHANGED_INSUFFICIENT_BUF_RESOURCES:
			vdec_event_change(inst, data, false);
			break;
		case HFI_EVENT_RELEASE_BUFFER_REFERENCE:
			venus_helper_release_buf_ref(inst, data->tag);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}