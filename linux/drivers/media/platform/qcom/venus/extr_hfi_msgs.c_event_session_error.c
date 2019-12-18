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
struct venus_inst {TYPE_1__* ops; int /*<<< orphan*/  error; } ;
struct venus_core {struct device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  session_id; } ;
struct hfi_msg_event_notify_pkt {int /*<<< orphan*/  event_data1; TYPE_2__ shdr; int /*<<< orphan*/  event_data2; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_notify ) (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVT_SESSION_ERROR ; 
 int /*<<< orphan*/  HFI_ERR_NONE ; 
#define  HFI_ERR_SESSION_INVALID_SCALE_FACTOR 131 
#define  HFI_ERR_SESSION_UNSUPPORTED_SETTING 130 
#define  HFI_ERR_SESSION_UNSUPPORT_BUFFERTYPE 129 
#define  HFI_ERR_SESSION_UPSCALE_NOT_SUPPORTED 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct venus_inst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
event_session_error(struct venus_core *core, struct venus_inst *inst,
		    struct hfi_msg_event_notify_pkt *pkt)
{
	struct device *dev = core->dev;

	dev_dbg(dev, "session error: event id:%x, session id:%x\n",
		pkt->event_data1, pkt->shdr.session_id);

	if (!inst)
		return;

	switch (pkt->event_data1) {
	/* non fatal session errors */
	case HFI_ERR_SESSION_INVALID_SCALE_FACTOR:
	case HFI_ERR_SESSION_UNSUPPORT_BUFFERTYPE:
	case HFI_ERR_SESSION_UNSUPPORTED_SETTING:
	case HFI_ERR_SESSION_UPSCALE_NOT_SUPPORTED:
		inst->error = HFI_ERR_NONE;
		break;
	default:
		dev_err(dev, "session error: event id:%x (%x), session id:%x\n",
			pkt->event_data1, pkt->event_data2,
			pkt->shdr.session_id);

		inst->error = pkt->event_data1;
		inst->ops->event_notify(inst, EVT_SESSION_ERROR, NULL);
		break;
	}
}