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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct mcu_msg_encode_frame_response {int /*<<< orphan*/  channel_id; TYPE_1__ header; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct allegro_channel {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_channel_finish_frame (struct allegro_channel*,struct mcu_msg_encode_frame_response*) ; 
 struct allegro_channel* allegro_find_channel_by_channel_id (struct allegro_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
allegro_handle_encode_frame(struct allegro_dev *dev,
			    struct mcu_msg_encode_frame_response *msg)
{
	struct allegro_channel *channel;

	channel = allegro_find_channel_by_channel_id(dev, msg->channel_id);
	if (IS_ERR(channel)) {
		v4l2_err(&dev->v4l2_dev,
			 "received %s for unknown channel %d\n",
			 msg_type_name(msg->header.type),
			 msg->channel_id);
		return -EINVAL;
	}

	allegro_channel_finish_frame(channel, msg);

	return 0;
}