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
struct videobuf_queue {struct via_camera* priv_data; } ;
struct videobuf_buffer {int field; scalar_t__ state; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sizeimage; } ;
struct via_camera {TYPE_1__ user_format; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 int videobuf_iolock (struct videobuf_queue*,struct videobuf_buffer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viacam_vb_buf_prepare(struct videobuf_queue *q,
		struct videobuf_buffer *vb, enum v4l2_field field)
{
	struct via_camera *cam = q->priv_data;

	vb->size = cam->user_format.sizeimage;
	vb->width = cam->user_format.width; /* bytesperline???? */
	vb->height = cam->user_format.height;
	vb->field = field;
	if (vb->state == VIDEOBUF_NEEDS_INIT) {
		int ret = videobuf_iolock(q, vb, NULL);
		if (ret)
			return ret;
	}
	vb->state = VIDEOBUF_PREPARED;
	return 0;
}