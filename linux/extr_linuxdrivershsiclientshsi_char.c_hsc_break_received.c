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
struct hsi_msg {int /*<<< orphan*/  cl; int /*<<< orphan*/  status; } ;
struct hsc_client_data {struct hsc_channel* channels; } ;
struct hsc_channel {int /*<<< orphan*/  rx_wait; int /*<<< orphan*/  rx_msgs_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/  free_msgs_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSC_CH_READ ; 
 int HSC_DEVS ; 
 int /*<<< orphan*/  HSI_STATUS_COMPLETED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hsc_add_tail (struct hsc_channel*,struct hsi_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hsc_break_req_destructor (struct hsi_msg*) ; 
 struct hsi_msg* hsc_get_first_msg (struct hsc_channel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hsc_msg_len_set (struct hsi_msg*,int /*<<< orphan*/ ) ; 
 int hsi_async_read (int /*<<< orphan*/ ,struct hsi_msg*) ; 
 struct hsc_client_data* hsi_client_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsc_break_received(struct hsi_msg *msg)
{
	struct hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);
	struct hsc_channel *channel = cl_data->channels;
	int i, ret;

	/* Broadcast HWBREAK on all channels */
	for (i = 0; i < HSC_DEVS; i++, channel++) {
		struct hsi_msg *msg2;

		if (!test_bit(HSC_CH_READ, &channel->flags))
			continue;
		msg2 = hsc_get_first_msg(channel, &channel->free_msgs_list);
		if (!msg2)
			continue;
		clear_bit(HSC_CH_READ, &channel->flags);
		hsc_msg_len_set(msg2, 0);
		msg2->status = HSI_STATUS_COMPLETED;
		hsc_add_tail(channel, msg2, &channel->rx_msgs_queue);
		wake_up(&channel->rx_wait);
	}
	hsi_flush(msg->cl);
	ret = hsi_async_read(msg->cl, msg);
	if (ret < 0)
		hsc_break_req_destructor(msg);
}