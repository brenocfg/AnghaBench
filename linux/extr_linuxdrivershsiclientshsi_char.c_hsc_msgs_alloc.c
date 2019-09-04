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
struct hsi_msg {int /*<<< orphan*/  link; int /*<<< orphan*/  channel; } ;
struct hsc_channel {int /*<<< orphan*/  free_msgs_list; int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HSC_MSGS ; 
 int /*<<< orphan*/  hsc_free_list (int /*<<< orphan*/ *) ; 
 struct hsi_msg* hsc_msg_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_data_size ; 

__attribute__((used)) static inline int hsc_msgs_alloc(struct hsc_channel *channel)
{
	struct hsi_msg *msg;
	int i;

	for (i = 0; i < HSC_MSGS; i++) {
		msg = hsc_msg_alloc(max_data_size);
		if (!msg)
			goto out;
		msg->channel = channel->ch;
		list_add_tail(&msg->link, &channel->free_msgs_list);
	}

	return 0;
out:
	hsc_free_list(&channel->free_msgs_list);

	return -ENOMEM;
}