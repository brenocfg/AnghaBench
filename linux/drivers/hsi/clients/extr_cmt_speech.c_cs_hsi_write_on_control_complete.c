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
struct hsi_msg {int /*<<< orphan*/  status; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {TYPE_1__* cl; int /*<<< orphan*/  lock; int /*<<< orphan*/  control_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSI_STATUS_COMPLETED ; 
 int /*<<< orphan*/  HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  SSI_CHANNEL_STATE_WRITING ; 
 int /*<<< orphan*/  cs_hsi_control_write_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_write_on_control_complete(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;
	if (msg->status == HSI_STATUS_COMPLETED) {
		spin_lock(&hi->lock);
		hi->control_state &= ~SSI_CHANNEL_STATE_WRITING;
		cs_release_cmd(msg);
		spin_unlock(&hi->lock);
	} else if (msg->status == HSI_STATUS_ERROR) {
		cs_hsi_control_write_error(hi, msg);
	} else {
		dev_err(&hi->cl->device,
			"unexpected status in control write callback %d\n",
			msg->status);
	}
}