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
struct vb2_queue {scalar_t__ type; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct allegro_channel {TYPE_1__ fh; struct allegro_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLEGRO_STATE_STOPPED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (scalar_t__) ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  allegro_destroy_channel (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_set_state (struct allegro_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 struct allegro_channel* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void allegro_stop_streaming(struct vb2_queue *q)
{
	struct allegro_channel *channel = vb2_get_drv_priv(q);
	struct allegro_dev *dev = channel->dev;
	struct vb2_v4l2_buffer *buffer;

	v4l2_dbg(2, debug, &dev->v4l2_dev,
		 "%s: stop streaming\n",
		 V4L2_TYPE_IS_OUTPUT(q->type) ? "output" : "capture");

	if (V4L2_TYPE_IS_OUTPUT(q->type)) {
		allegro_set_state(channel, ALLEGRO_STATE_STOPPED);
		while ((buffer = v4l2_m2m_src_buf_remove(channel->fh.m2m_ctx)))
			v4l2_m2m_buf_done(buffer, VB2_BUF_STATE_ERROR);
	} else if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		allegro_destroy_channel(channel);
		while ((buffer = v4l2_m2m_dst_buf_remove(channel->fh.m2m_ctx)))
			v4l2_m2m_buf_done(buffer, VB2_BUF_STATE_ERROR);
	}
}