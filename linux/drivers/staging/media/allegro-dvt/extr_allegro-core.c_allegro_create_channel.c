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
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  channel_user_ids; } ;
struct allegro_channel {scalar_t__ user_id; int level; int error; int /*<<< orphan*/  mcu_channel_id; int /*<<< orphan*/  completion; int /*<<< orphan*/  mpeg_video_gop_size; int /*<<< orphan*/  mpeg_video_cpb_size; int /*<<< orphan*/  mpeg_video_bitrate_peak; int /*<<< orphan*/  mpeg_video_bitrate; int /*<<< orphan*/  mpeg_video_bitrate_mode; int /*<<< orphan*/  mpeg_video_h264_level; int /*<<< orphan*/  mpeg_video_h264_profile; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  codec; struct allegro_dev* dev; } ;
typedef  enum v4l2_mpeg_video_h264_level { ____Placeholder_v4l2_mpeg_video_h264_level } v4l2_mpeg_video_h264_level ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  V4L2_CID_MPEG_VIDEO_H264_LEVEL ; 
 int /*<<< orphan*/  allegro_destroy_channel (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_mcu_send_create_channel (struct allegro_dev*,struct allegro_channel*) ; 
 scalar_t__ allegro_next_user_id (struct allegro_dev*) ; 
 scalar_t__ channel_exists (struct allegro_channel*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int select_minimum_h264_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * v4l2_ctrl_get_menu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_warn (int /*<<< orphan*/ *,char*,...) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_create_channel(struct allegro_channel *channel)
{
	struct allegro_dev *dev = channel->dev;
	unsigned long timeout;
	enum v4l2_mpeg_video_h264_level min_level;

	if (channel_exists(channel)) {
		v4l2_warn(&dev->v4l2_dev,
			  "channel already exists\n");
		return 0;
	}

	channel->user_id = allegro_next_user_id(dev);
	if (channel->user_id < 0) {
		v4l2_err(&dev->v4l2_dev,
			 "no free channels available\n");
		return -EBUSY;
	}
	set_bit(channel->user_id, &dev->channel_user_ids);

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "user %d: creating channel (%4.4s, %dx%d@%d)\n",
		 channel->user_id,
		 (char *)&channel->codec, channel->width, channel->height, 25);

	min_level = select_minimum_h264_level(channel->width, channel->height);
	if (channel->level < min_level) {
		v4l2_warn(&dev->v4l2_dev,
			  "user %d: selected Level %s too low: increasing to Level %s\n",
			  channel->user_id,
			  v4l2_ctrl_get_menu(V4L2_CID_MPEG_VIDEO_H264_LEVEL)[channel->level],
			  v4l2_ctrl_get_menu(V4L2_CID_MPEG_VIDEO_H264_LEVEL)[min_level]);
		channel->level = min_level;
	}

	v4l2_ctrl_grab(channel->mpeg_video_h264_profile, true);
	v4l2_ctrl_grab(channel->mpeg_video_h264_level, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_mode, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate, true);
	v4l2_ctrl_grab(channel->mpeg_video_bitrate_peak, true);
	v4l2_ctrl_grab(channel->mpeg_video_cpb_size, true);
	v4l2_ctrl_grab(channel->mpeg_video_gop_size, true);

	reinit_completion(&channel->completion);
	allegro_mcu_send_create_channel(dev, channel);
	timeout = wait_for_completion_timeout(&channel->completion,
					      msecs_to_jiffies(5000));
	if (timeout == 0)
		channel->error = -ETIMEDOUT;
	if (channel->error)
		goto err;

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "channel %d: accepting buffers\n",
		 channel->mcu_channel_id);

	return 0;

err:
	allegro_destroy_channel(channel);

	return channel->error;
}