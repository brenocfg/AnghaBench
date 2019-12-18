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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int nents; } ;
struct hsi_msg {int /*<<< orphan*/  complete; TYPE_1__ sgt; } ;
struct cs_hsi_iface {int control_state; TYPE_2__* cl; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int SSI_CHANNEL_STATE_ERROR ; 
 int SSI_CHANNEL_STATE_READING ; 
 int SSI_CHANNEL_STATE_WRITING ; 
 struct hsi_msg* cs_claim_cmd (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_control_write_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_read_on_control (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_hsi_write_on_control_complete ; 
 int /*<<< orphan*/  cs_set_cmd (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int hsi_async_write (TYPE_2__*,struct hsi_msg*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cs_hsi_write_on_control(struct cs_hsi_iface *hi, u32 message)
{
	struct hsi_msg *msg;
	int ret;

	spin_lock(&hi->lock);
	if (hi->control_state & SSI_CHANNEL_STATE_ERROR) {
		spin_unlock(&hi->lock);
		return -EIO;
	}
	if (hi->control_state & SSI_CHANNEL_STATE_WRITING) {
		dev_err(&hi->cl->device,
			"Write still pending on control channel.\n");
		spin_unlock(&hi->lock);
		return -EBUSY;
	}
	hi->control_state |= SSI_CHANNEL_STATE_WRITING;
	msg = cs_claim_cmd(hi);
	spin_unlock(&hi->lock);

	cs_set_cmd(msg, message);
	msg->sgt.nents = 1;
	msg->complete = cs_hsi_write_on_control_complete;
	dev_dbg(&hi->cl->device,
		"Sending control message %08X\n", message);
	ret = hsi_async_write(hi->cl, msg);
	if (ret) {
		dev_err(&hi->cl->device,
			"async_write failed with %d\n", ret);
		cs_hsi_control_write_error(hi, msg);
	}

	/*
	 * Make sure control read is always pending when issuing
	 * new control writes. This is needed as the controller
	 * may flush our messages if e.g. the peer device reboots
	 * unexpectedly (and we cannot directly resubmit a new read from
	 * the message destructor; see cs_cmd_destructor()).
	 */
	if (!(hi->control_state & SSI_CHANNEL_STATE_READING)) {
		dev_err(&hi->cl->device, "Restarting control reads\n");
		cs_hsi_read_on_control(hi);
	}

	return 0;
}