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
struct qcom_smd_edge {int /*<<< orphan*/  dev; } ;
struct qcom_smd_channel {scalar_t__ remote_state; int /*<<< orphan*/  state_change_event; int /*<<< orphan*/  bounce_buffer; int /*<<< orphan*/  fifo_size; struct qcom_smd_edge* edge; } ;
typedef  int /*<<< orphan*/  rpmsg_rx_cb_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ SMD_CHANNEL_CLOSED ; 
 scalar_t__ SMD_CHANNEL_OPENED ; 
 scalar_t__ SMD_CHANNEL_OPENING ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 
 size_t min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_channel_set_callback (struct qcom_smd_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_smd_channel_set_state (struct qcom_smd_channel*,scalar_t__) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_smd_channel_open(struct qcom_smd_channel *channel,
				 rpmsg_rx_cb_t cb)
{
	struct qcom_smd_edge *edge = channel->edge;
	size_t bb_size;
	int ret;

	/*
	 * Packets are maximum 4k, but reduce if the fifo is smaller
	 */
	bb_size = min(channel->fifo_size, SZ_4K);
	channel->bounce_buffer = kmalloc(bb_size, GFP_KERNEL);
	if (!channel->bounce_buffer)
		return -ENOMEM;

	qcom_smd_channel_set_callback(channel, cb);
	qcom_smd_channel_set_state(channel, SMD_CHANNEL_OPENING);

	/* Wait for remote to enter opening or opened */
	ret = wait_event_interruptible_timeout(channel->state_change_event,
			channel->remote_state == SMD_CHANNEL_OPENING ||
			channel->remote_state == SMD_CHANNEL_OPENED,
			HZ);
	if (!ret) {
		dev_err(&edge->dev, "remote side did not enter opening state\n");
		goto out_close_timeout;
	}

	qcom_smd_channel_set_state(channel, SMD_CHANNEL_OPENED);

	/* Wait for remote to enter opened */
	ret = wait_event_interruptible_timeout(channel->state_change_event,
			channel->remote_state == SMD_CHANNEL_OPENED,
			HZ);
	if (!ret) {
		dev_err(&edge->dev, "remote side did not enter open state\n");
		goto out_close_timeout;
	}

	return 0;

out_close_timeout:
	qcom_smd_channel_set_state(channel, SMD_CHANNEL_CLOSED);
	return -ETIMEDOUT;
}