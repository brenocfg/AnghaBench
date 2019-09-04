#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int flags; scalar_t__ field; scalar_t__ sequence; } ;
struct vb2_queue {int /*<<< orphan*/  copy_timestamp; scalar_t__ allow_zero_bytesused; scalar_t__ is_output; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; } ;
struct vb2_plane {scalar_t__ length; scalar_t__ bytesused; TYPE_2__ m; int /*<<< orphan*/  data_offset; } ;
struct vb2_buffer {unsigned int num_planes; struct vb2_queue* vb2_queue; scalar_t__ timestamp; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; } ;
struct v4l2_plane {scalar_t__ length; scalar_t__ bytesused; int /*<<< orphan*/  data_offset; TYPE_1__ m; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; struct v4l2_plane* planes; } ;
struct v4l2_buffer {scalar_t__ field; scalar_t__ memory; scalar_t__ length; scalar_t__ bytesused; int flags; int /*<<< orphan*/  type; TYPE_3__ m; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUFFER_MASK_FLAGS ; 
 int V4L2_BUFFER_OUT_FLAGS ; 
 int V4L2_BUF_FLAG_LAST ; 
 int V4L2_BUF_FLAG_TIMECODE ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
 scalar_t__ V4L2_FIELD_ALTERNATE ; 
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ VB2_MEMORY_DMABUF ; 
 scalar_t__ VB2_MEMORY_USERPTR ; 
 int __verify_length (struct vb2_buffer*,struct v4l2_buffer const*) ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 int /*<<< orphan*/  vb2_warn_zero_bytesused (struct vb2_buffer*) ; 

__attribute__((used)) static int __fill_vb2_buffer(struct vb2_buffer *vb,
		const void *pb, struct vb2_plane *planes)
{
	struct vb2_queue *q = vb->vb2_queue;
	const struct v4l2_buffer *b = pb;
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	unsigned int plane;
	int ret;

	ret = __verify_length(vb, b);
	if (ret < 0) {
		dprintk(1, "plane parameters verification failed: %d\n", ret);
		return ret;
	}
	if (b->field == V4L2_FIELD_ALTERNATE && q->is_output) {
		/*
		 * If the format's field is ALTERNATE, then the buffer's field
		 * should be either TOP or BOTTOM, not ALTERNATE since that
		 * makes no sense. The driver has to know whether the
		 * buffer represents a top or a bottom field in order to
		 * program any DMA correctly. Using ALTERNATE is wrong, since
		 * that just says that it is either a top or a bottom field,
		 * but not which of the two it is.
		 */
		dprintk(1, "the field is incorrectly set to ALTERNATE for an output buffer\n");
		return -EINVAL;
	}
	vb->timestamp = 0;
	vbuf->sequence = 0;

	if (V4L2_TYPE_IS_MULTIPLANAR(b->type)) {
		if (b->memory == VB2_MEMORY_USERPTR) {
			for (plane = 0; plane < vb->num_planes; ++plane) {
				planes[plane].m.userptr =
					b->m.planes[plane].m.userptr;
				planes[plane].length =
					b->m.planes[plane].length;
			}
		}
		if (b->memory == VB2_MEMORY_DMABUF) {
			for (plane = 0; plane < vb->num_planes; ++plane) {
				planes[plane].m.fd =
					b->m.planes[plane].m.fd;
				planes[plane].length =
					b->m.planes[plane].length;
			}
		}

		/* Fill in driver-provided information for OUTPUT types */
		if (V4L2_TYPE_IS_OUTPUT(b->type)) {
			/*
			 * Will have to go up to b->length when API starts
			 * accepting variable number of planes.
			 *
			 * If bytesused == 0 for the output buffer, then fall
			 * back to the full buffer size. In that case
			 * userspace clearly never bothered to set it and
			 * it's a safe assumption that they really meant to
			 * use the full plane sizes.
			 *
			 * Some drivers, e.g. old codec drivers, use bytesused == 0
			 * as a way to indicate that streaming is finished.
			 * In that case, the driver should use the
			 * allow_zero_bytesused flag to keep old userspace
			 * applications working.
			 */
			for (plane = 0; plane < vb->num_planes; ++plane) {
				struct vb2_plane *pdst = &planes[plane];
				struct v4l2_plane *psrc = &b->m.planes[plane];

				if (psrc->bytesused == 0)
					vb2_warn_zero_bytesused(vb);

				if (vb->vb2_queue->allow_zero_bytesused)
					pdst->bytesused = psrc->bytesused;
				else
					pdst->bytesused = psrc->bytesused ?
						psrc->bytesused : pdst->length;
				pdst->data_offset = psrc->data_offset;
			}
		}
	} else {
		/*
		 * Single-planar buffers do not use planes array,
		 * so fill in relevant v4l2_buffer struct fields instead.
		 * In videobuf we use our internal V4l2_planes struct for
		 * single-planar buffers as well, for simplicity.
		 *
		 * If bytesused == 0 for the output buffer, then fall back
		 * to the full buffer size as that's a sensible default.
		 *
		 * Some drivers, e.g. old codec drivers, use bytesused == 0 as
		 * a way to indicate that streaming is finished. In that case,
		 * the driver should use the allow_zero_bytesused flag to keep
		 * old userspace applications working.
		 */
		if (b->memory == VB2_MEMORY_USERPTR) {
			planes[0].m.userptr = b->m.userptr;
			planes[0].length = b->length;
		}

		if (b->memory == VB2_MEMORY_DMABUF) {
			planes[0].m.fd = b->m.fd;
			planes[0].length = b->length;
		}

		if (V4L2_TYPE_IS_OUTPUT(b->type)) {
			if (b->bytesused == 0)
				vb2_warn_zero_bytesused(vb);

			if (vb->vb2_queue->allow_zero_bytesused)
				planes[0].bytesused = b->bytesused;
			else
				planes[0].bytesused = b->bytesused ?
					b->bytesused : planes[0].length;
		} else
			planes[0].bytesused = 0;

	}

	/* Zero flags that the vb2 core handles */
	vbuf->flags = b->flags & ~V4L2_BUFFER_MASK_FLAGS;
	if (!vb->vb2_queue->copy_timestamp || !V4L2_TYPE_IS_OUTPUT(b->type)) {
		/*
		 * Non-COPY timestamps and non-OUTPUT queues will get
		 * their timestamp and timestamp source flags from the
		 * queue.
		 */
		vbuf->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	}

	if (V4L2_TYPE_IS_OUTPUT(b->type)) {
		/*
		 * For output buffers mask out the timecode flag:
		 * this will be handled later in vb2_qbuf().
		 * The 'field' is valid metadata for this output buffer
		 * and so that needs to be copied here.
		 */
		vbuf->flags &= ~V4L2_BUF_FLAG_TIMECODE;
		vbuf->field = b->field;
	} else {
		/* Zero any output buffer flags as this is a capture buffer */
		vbuf->flags &= ~V4L2_BUFFER_OUT_FLAGS;
		/* Zero last flag, this is a signal from driver to userspace */
		vbuf->flags &= ~V4L2_BUF_FLAG_LAST;
	}

	return 0;
}