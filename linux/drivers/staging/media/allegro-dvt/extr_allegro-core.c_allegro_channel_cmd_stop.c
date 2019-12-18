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
struct vb2_v4l2_buffer {int dummy; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct allegro_channel {int /*<<< orphan*/  mcu_channel_id; TYPE_1__ fh; struct allegro_dev* dev; } ;

/* Variables and functions */
#define  ALLEGRO_STATE_DRAIN 130 
#define  ALLEGRO_STATE_ENCODING 129 
#define  ALLEGRO_STATE_WAIT_FOR_BUFFER 128 
 int EBUSY ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  allegro_channel_buf_done (struct allegro_channel*,struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 int allegro_get_state (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_set_state (struct allegro_channel*,int const) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_channel_cmd_stop(struct allegro_channel *channel)
{
	struct allegro_dev *dev = channel->dev;
	struct vb2_v4l2_buffer *dst_buf;

	switch (allegro_get_state(channel)) {
	case ALLEGRO_STATE_DRAIN:
	case ALLEGRO_STATE_WAIT_FOR_BUFFER:
		return -EBUSY;
	case ALLEGRO_STATE_ENCODING:
		allegro_set_state(channel, ALLEGRO_STATE_DRAIN);
		break;
	default:
		return 0;
	}

	/* If there are output buffers, they must be encoded */
	if (v4l2_m2m_num_src_bufs_ready(channel->fh.m2m_ctx) != 0) {
		v4l2_dbg(1, debug,  &dev->v4l2_dev,
			 "channel %d: CMD_STOP: continue encoding src buffers\n",
			 channel->mcu_channel_id);
		return 0;
	}

	/* If there are capture buffers, use it to signal EOS */
	dst_buf = v4l2_m2m_dst_buf_remove(channel->fh.m2m_ctx);
	if (dst_buf) {
		v4l2_dbg(1, debug,  &dev->v4l2_dev,
			 "channel %d: CMD_STOP: signaling EOS\n",
			 channel->mcu_channel_id);
		allegro_channel_buf_done(channel, dst_buf, VB2_BUF_STATE_DONE);
		return 0;
	}

	/*
	 * If there are no capture buffers, we need to wait for the next
	 * buffer to signal EOS.
	 */
	v4l2_dbg(1, debug,  &dev->v4l2_dev,
		 "channel %d: CMD_STOP: wait for CAPTURE buffer to signal EOS\n",
		 channel->mcu_channel_id);
	allegro_set_state(channel, ALLEGRO_STATE_WAIT_FOR_BUFFER);

	return 0;
}