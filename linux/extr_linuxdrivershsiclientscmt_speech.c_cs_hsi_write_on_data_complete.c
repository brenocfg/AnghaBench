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
struct hsi_msg {scalar_t__ status; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {int /*<<< orphan*/  lock; int /*<<< orphan*/  datawait; int /*<<< orphan*/  data_state; } ;

/* Variables and functions */
 scalar_t__ HSI_STATUS_COMPLETED ; 
 int /*<<< orphan*/  SSI_CHANNEL_STATE_WRITING ; 
 int /*<<< orphan*/  cs_hsi_data_write_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_write_on_data_complete(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;

	if (msg->status == HSI_STATUS_COMPLETED) {
		spin_lock(&hi->lock);
		hi->data_state &= ~SSI_CHANNEL_STATE_WRITING;
		if (unlikely(waitqueue_active(&hi->datawait)))
			wake_up_interruptible(&hi->datawait);
		spin_unlock(&hi->lock);
	} else {
		cs_hsi_data_write_error(hi, msg);
	}
}