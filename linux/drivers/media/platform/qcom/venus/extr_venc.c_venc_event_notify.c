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
typedef  scalar_t__ u32 ;
struct venus_inst {int session_error; int /*<<< orphan*/  error; TYPE_1__* core; } ;
struct hfi_event_data {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev_enc; } ;

/* Variables and functions */
 scalar_t__ EVT_SESSION_ERROR ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venc_event_notify(struct venus_inst *inst, u32 event,
			      struct hfi_event_data *data)
{
	struct device *dev = inst->core->dev_enc;

	if (event == EVT_SESSION_ERROR) {
		inst->session_error = true;
		dev_err(dev, "enc: event session error %x\n", inst->error);
	}
}