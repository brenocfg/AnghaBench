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
struct vb2_v4l2_buffer {int /*<<< orphan*/  flags; } ;
struct v4l2_event {int /*<<< orphan*/  type; } ;
struct allegro_channel {int /*<<< orphan*/  fh; } ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;

/* Variables and functions */
 int /*<<< orphan*/  ALLEGRO_STATE_STOPPED ; 
 int /*<<< orphan*/  V4L2_BUF_FLAG_LAST ; 
 int /*<<< orphan*/  V4L2_EVENT_EOS ; 
 scalar_t__ allegro_channel_is_at_eos (struct allegro_channel*) ; 
 int /*<<< orphan*/  allegro_set_state (struct allegro_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_event_queue_fh (int /*<<< orphan*/ *,struct v4l2_event const*) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 

__attribute__((used)) static void allegro_channel_buf_done(struct allegro_channel *channel,
				     struct vb2_v4l2_buffer *buf,
				     enum vb2_buffer_state state)
{
	const struct v4l2_event eos_event = {
		.type = V4L2_EVENT_EOS
	};

	if (allegro_channel_is_at_eos(channel)) {
		buf->flags |= V4L2_BUF_FLAG_LAST;
		v4l2_event_queue_fh(&channel->fh, &eos_event);

		allegro_set_state(channel, ALLEGRO_STATE_STOPPED);
	}

	v4l2_m2m_buf_done(buf, state);
}