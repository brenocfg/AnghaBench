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
struct video_i2c_data {TYPE_1__* chip; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  field; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_2__ {unsigned int buffer_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct video_i2c_data* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned int vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct video_i2c_data *data = vb2_get_drv_priv(vb->vb2_queue);
	unsigned int size = data->chip->buffer_size;

	if (vb2_plane_size(vb, 0) < size)
		return -EINVAL;

	vbuf->field = V4L2_FIELD_NONE;
	vb2_set_plane_payload(vb, 0, size);

	return 0;
}