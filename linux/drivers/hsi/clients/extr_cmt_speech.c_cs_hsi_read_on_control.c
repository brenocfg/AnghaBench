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
struct TYPE_3__ {scalar_t__ nents; } ;
struct hsi_msg {int /*<<< orphan*/  complete; TYPE_1__ sgt; } ;
struct cs_hsi_iface {int control_state; TYPE_2__* cl; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int SSI_CHANNEL_STATE_ERROR ; 
 int SSI_CHANNEL_STATE_READING ; 
 struct hsi_msg* cs_claim_cmd (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_control_read_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_peek_on_control_complete ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hsi_async_read (TYPE_2__*,struct hsi_msg*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_read_on_control(struct cs_hsi_iface *hi)
{
	struct hsi_msg *msg;
	int ret;

	spin_lock(&hi->lock);
	if (hi->control_state & SSI_CHANNEL_STATE_READING) {
		dev_err(&hi->cl->device, "Control read already pending (%d)\n",
			hi->control_state);
		spin_unlock(&hi->lock);
		return;
	}
	if (hi->control_state & SSI_CHANNEL_STATE_ERROR) {
		dev_err(&hi->cl->device, "Control read error (%d)\n",
			hi->control_state);
		spin_unlock(&hi->lock);
		return;
	}
	hi->control_state |= SSI_CHANNEL_STATE_READING;
	dev_dbg(&hi->cl->device, "Issuing RX on control\n");
	msg = cs_claim_cmd(hi);
	spin_unlock(&hi->lock);

	msg->sgt.nents = 0;
	msg->complete = cs_hsi_peek_on_control_complete;
	ret = hsi_async_read(hi->cl, msg);
	if (ret)
		cs_hsi_control_read_error(hi, msg);
}