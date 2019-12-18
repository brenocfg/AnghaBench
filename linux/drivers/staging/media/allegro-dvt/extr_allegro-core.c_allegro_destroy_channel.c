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
struct allegro_dev {int /*<<< orphan*/  channel_user_ids; int /*<<< orphan*/  v4l2_dev; } ;
struct allegro_channel {int mcu_channel_id; int user_id; int /*<<< orphan*/  mpeg_video_gop_size; int /*<<< orphan*/  mpeg_video_cpb_size; int /*<<< orphan*/  mpeg_video_bitrate_peak; int /*<<< orphan*/  mpeg_video_bitrate; int /*<<< orphan*/  mpeg_video_bitrate_mode; int /*<<< orphan*/  mpeg_video_h264_level; int /*<<< orphan*/  mpeg_video_h264_profile; int /*<<< orphan*/  completion; struct allegro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  allegro_mcu_send_destroy_channel (struct allegro_dev*,struct allegro_channel*) ; 
 scalar_t__ channel_exists (struct allegro_channel*) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_intermediate_buffers (struct allegro_channel*) ; 
 int /*<<< orphan*/  destroy_reference_buffers (struct allegro_channel*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,int) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allegro_destroy_channel(struct allegro_channel *channel)
{
	struct allegro_dev *dev = channel->dev;
	unsigned long timeout;

	if (channel_exists(channel)) {
		reinit_completion(&channel->completion);
		allegro_mcu_send_destroy_channel(dev, channel);
		timeout = wait_for_completion_timeout(&channel->completion,
						      msecs_to_jiffies(5000));
		if (timeout == 0)
			v4l2_warn(&dev->v4l2_dev,
				  "channel %d: timeout while destroying\n",
				  channel->mcu_channel_id);

		channel->mcu_channel_id = -1;
	}

	destroy_intermediate_buffers(channel);
	destroy_reference_buffers(channel);

	v4l2_ctrl_grab(channel->mpeg_video_h264_profile, false);
	v4l2_ctrl_grab(channel->mpeg_video_h264_level, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_mode, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate, false);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_peak, false);
	v4l2_ctrl_grab(channel->mpeg_video_cpb_size, false);
	v4l2_ctrl_grab(channel->mpeg_video_gop_size, false);

	if (channel->user_id != -1) {
		clear_bit(channel->user_id, &dev->channel_user_ids);
		channel->user_id = -1;
	}
}