#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  timestamp; TYPE_1__* planes; } ;
struct vb2_v4l2_buffer {TYPE_3__ vb2_buf; int /*<<< orphan*/  field; int /*<<< orphan*/  sequence; } ;
struct TYPE_6__ {int /*<<< orphan*/  sizeimage; } ;
struct mcam_camera {TYPE_2__ pix_format; int /*<<< orphan*/ * buf_seq; } ;
struct TYPE_5__ {int /*<<< orphan*/  bytesused; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcam_buffer_done(struct mcam_camera *cam, int frame,
		struct vb2_v4l2_buffer *vbuf)
{
	vbuf->vb2_buf.planes[0].bytesused = cam->pix_format.sizeimage;
	vbuf->sequence = cam->buf_seq[frame];
	vbuf->field = V4L2_FIELD_NONE;
	vbuf->vb2_buf.timestamp = ktime_get_ns();
	vb2_set_plane_payload(&vbuf->vb2_buf, 0, cam->pix_format.sizeimage);
	vb2_buffer_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);
}