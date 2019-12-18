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
struct mcu_msg_create_channel_response {int /*<<< orphan*/  rec_buffers_size; int /*<<< orphan*/  rec_buffers_count; int /*<<< orphan*/  int_buffers_size; int /*<<< orphan*/  int_buffers_count; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  error_code; int /*<<< orphan*/  user_id; TYPE_1__ header; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct allegro_channel {int error; int /*<<< orphan*/  completion; int /*<<< orphan*/  mcu_channel_id; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct allegro_channel*) ; 
 struct allegro_channel* allegro_find_channel_by_user_id (struct allegro_dev*,int /*<<< orphan*/ ) ; 
 int allegro_mcu_push_buffer_intermediate (struct allegro_channel*) ; 
 int allegro_mcu_push_buffer_reference (struct allegro_channel*) ; 
 int allocate_intermediate_buffers (struct allegro_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int allocate_reference_buffers (struct allegro_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  msg_type_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
allegro_handle_create_channel(struct allegro_dev *dev,
			      struct mcu_msg_create_channel_response *msg)
{
	struct allegro_channel *channel;
	int err = 0;

	channel = allegro_find_channel_by_user_id(dev, msg->user_id);
	if (IS_ERR(channel)) {
		v4l2_warn(&dev->v4l2_dev,
			  "received %s for unknown user %d\n",
			  msg_type_name(msg->header.type),
			  msg->user_id);
		return -EINVAL;
	}

	if (msg->error_code) {
		v4l2_err(&dev->v4l2_dev,
			 "user %d: mcu failed to create channel: error %x\n",
			 channel->user_id, msg->error_code);
		err = -EIO;
		goto out;
	}

	channel->mcu_channel_id = msg->channel_id;
	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "user %d: channel has channel id %d\n",
		 channel->user_id, channel->mcu_channel_id);

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: intermediate buffers: %d x %d bytes\n",
		 channel->mcu_channel_id,
		 msg->int_buffers_count, msg->int_buffers_size);
	err = allocate_intermediate_buffers(channel, msg->int_buffers_count,
					    msg->int_buffers_size);
	if (err) {
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: failed to allocate intermediate buffers\n",
			 channel->mcu_channel_id);
		goto out;
	}
	err = allegro_mcu_push_buffer_intermediate(channel);
	if (err)
		goto out;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: reference buffers: %d x %d bytes\n",
		 channel->mcu_channel_id,
		 msg->rec_buffers_count, msg->rec_buffers_size);
	err = allocate_reference_buffers(channel, msg->rec_buffers_count,
					 msg->rec_buffers_size);
	if (err) {
		v4l2_err(&dev->v4l2_dev,
			 "channel %d: failed to allocate reference buffers\n",
			 channel->mcu_channel_id);
		goto out;
	}
	err = allegro_mcu_push_buffer_reference(channel);
	if (err)
		goto out;

out:
	channel->error = err;
	complete(&channel->completion);

	/* Handled successfully, error is passed via channel->error */
	return 0;
}