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
struct vb2_v4l2_buffer {scalar_t__ field; } ;
struct vb2_buffer {TYPE_1__* vb2_queue; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; } ;
struct allegro_channel {int /*<<< orphan*/  mcu_channel_id; struct allegro_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ ALLEGRO_STATE_DRAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ allegro_get_state (struct allegro_channel*) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct allegro_channel* vb2_get_drv_priv (TYPE_1__*) ; 

__attribute__((used)) static int allegro_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct allegro_channel *channel = vb2_get_drv_priv(vb->vb2_queue);
	struct allegro_dev *dev = channel->dev;

	if (allegro_get_state(channel) == ALLEGRO_STATE_DRAIN &&
	    V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type))
		return -EBUSY;

	if (V4L2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		if (vbuf->field == V4L2_FIELD_ANY)
			vbuf->field = V4L2_FIELD_NONE;
		if (vbuf->field != V4L2_FIELD_NONE) {
			v4l2_err(&dev->v4l2_dev,
				 "channel %d: unsupported field\n",
				 channel->mcu_channel_id);
			return -EINVAL;
		}
	}

	return 0;
}