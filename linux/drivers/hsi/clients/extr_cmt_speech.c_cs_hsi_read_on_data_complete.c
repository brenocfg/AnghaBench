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
typedef  int /*<<< orphan*/  u32 ;
struct hsi_msg {scalar_t__ status; struct cs_hsi_iface* context; } ;
struct cs_hsi_iface {int data_state; int /*<<< orphan*/  rx_bufs; int /*<<< orphan*/  lock; int /*<<< orphan*/  datawait; int /*<<< orphan*/  rx_slot; TYPE_1__* mmap_cfg; int /*<<< orphan*/  rx_ptr_boundary; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_RX_DATA_RECEIVED ; 
 scalar_t__ HSI_STATUS_ERROR ; 
 int SSI_CHANNEL_STATE_READING ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cs_hsi_data_read_error (struct cs_hsi_iface*,struct hsi_msg*) ; 
 int /*<<< orphan*/  cs_hsi_read_on_data (struct cs_hsi_iface*) ; 
 int /*<<< orphan*/  cs_notify_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_hsi_read_on_data_complete(struct hsi_msg *msg)
{
	struct cs_hsi_iface *hi = msg->context;
	u32 payload;

	if (unlikely(msg->status == HSI_STATUS_ERROR)) {
		cs_hsi_data_read_error(hi, msg);
		return;
	}

	spin_lock(&hi->lock);
	WARN_ON(!(hi->data_state & SSI_CHANNEL_STATE_READING));
	hi->data_state &= ~SSI_CHANNEL_STATE_READING;
	payload = CS_RX_DATA_RECEIVED;
	payload |= hi->rx_slot;
	hi->rx_slot++;
	hi->rx_slot %= hi->rx_ptr_boundary;
	/* expose current rx ptr in mmap area */
	hi->mmap_cfg->rx_ptr = hi->rx_slot;
	if (unlikely(waitqueue_active(&hi->datawait)))
		wake_up_interruptible(&hi->datawait);
	spin_unlock(&hi->lock);

	cs_notify_data(payload, hi->rx_bufs);
	cs_hsi_read_on_data(hi);
}