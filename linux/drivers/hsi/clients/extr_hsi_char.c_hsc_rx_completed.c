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
struct hsi_msg {int /*<<< orphan*/  channel; int /*<<< orphan*/  cl; } ;
struct hsc_client_data {struct hsc_channel* channels; } ;
struct hsc_channel {int /*<<< orphan*/  free_msgs_list; int /*<<< orphan*/  rx_wait; int /*<<< orphan*/  rx_msgs_queue; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSC_CH_READ ; 
 int /*<<< orphan*/  hsc_add_tail (struct hsc_channel*,struct hsi_msg*,int /*<<< orphan*/ *) ; 
 struct hsc_client_data* hsi_client_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hsc_rx_completed(struct hsi_msg *msg)
{
	struct hsc_client_data *cl_data = hsi_client_drvdata(msg->cl);
	struct hsc_channel *channel = cl_data->channels + msg->channel;

	if (test_bit(HSC_CH_READ, &channel->flags)) {
		hsc_add_tail(channel, msg, &channel->rx_msgs_queue);
		wake_up(&channel->rx_wait);
	} else {
		hsc_add_tail(channel, msg, &channel->free_msgs_list);
	}
}