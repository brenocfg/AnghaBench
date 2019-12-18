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
struct timespec64 {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct hsi_msg {scalar_t__ status; struct cs_hsi_iface* context; } ;
struct cs_timestamp {void* tv_nsec; void* tv_sec; } ;
struct cs_hsi_iface {int flags; int /*<<< orphan*/  lock; TYPE_2__* mmap_cfg; TYPE_1__* cl; int /*<<< orphan*/  control_state; } ;
typedef  void* __u32 ;
struct TYPE_4__ {struct cs_timestamp tstamp_rx_ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int CS_FEAT_TSTAMP_RX_CTRL ; 
 scalar_t__ HSI_STATUS_ERROR ; 
 int /*<<< orphan*/  SSI_CHANNEL_STATE_READING ; 
 int /*<<< orphan*/  cs_get_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_control_read_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_read_on_control (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_notify_control (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_release_cmd (struct hsi_msg*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_read_on_control_complete(struct hsi_msg *msg)
{
	u32 cmd = cs_get_cmd(msg);
	struct cs_hsi_iface *hi = msg->context;

	spin_lock(&hi->lock);
	hi->control_state &= ~SSI_CHANNEL_STATE_READING;
	if (msg->status == HSI_STATUS_ERROR) {
		dev_err(&hi->cl->device, "Control RX error detected\n");
		spin_unlock(&hi->lock);
		cs_hsi_control_read_error(hi, msg);
		goto out;
	}
	dev_dbg(&hi->cl->device, "Read on control: %08X\n", cmd);
	cs_release_cmd(msg);
	if (hi->flags & CS_FEAT_TSTAMP_RX_CTRL) {
		struct timespec64 tspec;
		struct cs_timestamp *tstamp =
			&hi->mmap_cfg->tstamp_rx_ctrl;

		ktime_get_ts64(&tspec);

		tstamp->tv_sec = (__u32) tspec.tv_sec;
		tstamp->tv_nsec = (__u32) tspec.tv_nsec;
	}
	spin_unlock(&hi->lock);

	cs_notify_control(cmd);

out:
	cs_hsi_read_on_control(hi);
}