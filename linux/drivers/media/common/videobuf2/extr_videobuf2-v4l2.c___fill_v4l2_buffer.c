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
struct vb2_v4l2_buffer {int flags; scalar_t__ request_fd; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; int /*<<< orphan*/  field; } ;
struct vb2_queue {scalar_t__ memory; int timestamp_flags; int /*<<< orphan*/  copy_timestamp; scalar_t__ is_multiplanar; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; int /*<<< orphan*/  offset; } ;
struct vb2_plane {unsigned int length; TYPE_3__ m; scalar_t__ bytesused; int /*<<< orphan*/  data_offset; } ;
struct vb2_buffer {unsigned int num_planes; int state; scalar_t__ prepared; scalar_t__ synced; struct vb2_plane* planes; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; int /*<<< orphan*/  index; struct vb2_queue* vb2_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; int /*<<< orphan*/  mem_offset; } ;
struct v4l2_plane {unsigned int length; int /*<<< orphan*/  reserved; int /*<<< orphan*/  data_offset; TYPE_1__ m; scalar_t__ bytesused; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  userptr; int /*<<< orphan*/  offset; struct v4l2_plane* planes; } ;
struct v4l2_buffer {int flags; scalar_t__ request_fd; unsigned int length; TYPE_2__ m; scalar_t__ bytesused; scalar_t__ reserved2; int /*<<< orphan*/  sequence; int /*<<< orphan*/  timecode; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  field; int /*<<< orphan*/  memory; int /*<<< orphan*/  type; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int V4L2_BUFFER_MASK_FLAGS ; 
 int V4L2_BUF_FLAG_DONE ; 
 int V4L2_BUF_FLAG_ERROR ; 
 int V4L2_BUF_FLAG_IN_REQUEST ; 
 int V4L2_BUF_FLAG_MAPPED ; 
 int V4L2_BUF_FLAG_PREPARED ; 
 int V4L2_BUF_FLAG_QUEUED ; 
 int V4L2_BUF_FLAG_REQUEST_FD ; 
 int V4L2_BUF_FLAG_TIMESTAMP_MASK ; 
 int V4L2_BUF_FLAG_TSTAMP_SRC_MASK ; 
#define  VB2_BUF_STATE_ACTIVE 134 
#define  VB2_BUF_STATE_DEQUEUED 133 
#define  VB2_BUF_STATE_DONE 132 
#define  VB2_BUF_STATE_ERROR 131 
#define  VB2_BUF_STATE_IN_REQUEST 130 
#define  VB2_BUF_STATE_PREPARING 129 
#define  VB2_BUF_STATE_QUEUED 128 
 scalar_t__ VB2_MEMORY_DMABUF ; 
 scalar_t__ VB2_MEMORY_MMAP ; 
 scalar_t__ VB2_MEMORY_USERPTR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_timeval (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 scalar_t__ vb2_buffer_in_use (struct vb2_queue*,struct vb2_buffer*) ; 

__attribute__((used)) static void __fill_v4l2_buffer(struct vb2_buffer *vb, void *pb)
{
	struct v4l2_buffer *b = pb;
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vb2_queue *q = vb->vb2_queue;
	unsigned int plane;

	/* Copy back data such as timestamp, flags, etc. */
	b->index = vb->index;
	b->type = vb->type;
	b->memory = vb->memory;
	b->bytesused = 0;

	b->flags = vbuf->flags;
	b->field = vbuf->field;
	b->timestamp = ns_to_timeval(vb->timestamp);
	b->timecode = vbuf->timecode;
	b->sequence = vbuf->sequence;
	b->reserved2 = 0;
	b->request_fd = 0;

	if (q->is_multiplanar) {
		/*
		 * Fill in plane-related data if userspace provided an array
		 * for it. The caller has already verified memory and size.
		 */
		b->length = vb->num_planes;
		for (plane = 0; plane < vb->num_planes; ++plane) {
			struct v4l2_plane *pdst = &b->m.planes[plane];
			struct vb2_plane *psrc = &vb->planes[plane];

			pdst->bytesused = psrc->bytesused;
			pdst->length = psrc->length;
			if (q->memory == VB2_MEMORY_MMAP)
				pdst->m.mem_offset = psrc->m.offset;
			else if (q->memory == VB2_MEMORY_USERPTR)
				pdst->m.userptr = psrc->m.userptr;
			else if (q->memory == VB2_MEMORY_DMABUF)
				pdst->m.fd = psrc->m.fd;
			pdst->data_offset = psrc->data_offset;
			memset(pdst->reserved, 0, sizeof(pdst->reserved));
		}
	} else {
		/*
		 * We use length and offset in v4l2_planes array even for
		 * single-planar buffers, but userspace does not.
		 */
		b->length = vb->planes[0].length;
		b->bytesused = vb->planes[0].bytesused;
		if (q->memory == VB2_MEMORY_MMAP)
			b->m.offset = vb->planes[0].m.offset;
		else if (q->memory == VB2_MEMORY_USERPTR)
			b->m.userptr = vb->planes[0].m.userptr;
		else if (q->memory == VB2_MEMORY_DMABUF)
			b->m.fd = vb->planes[0].m.fd;
	}

	/*
	 * Clear any buffer state related flags.
	 */
	b->flags &= ~V4L2_BUFFER_MASK_FLAGS;
	b->flags |= q->timestamp_flags & V4L2_BUF_FLAG_TIMESTAMP_MASK;
	if (!q->copy_timestamp) {
		/*
		 * For non-COPY timestamps, drop timestamp source bits
		 * and obtain the timestamp source from the queue.
		 */
		b->flags &= ~V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
		b->flags |= q->timestamp_flags & V4L2_BUF_FLAG_TSTAMP_SRC_MASK;
	}

	switch (vb->state) {
	case VB2_BUF_STATE_QUEUED:
	case VB2_BUF_STATE_ACTIVE:
		b->flags |= V4L2_BUF_FLAG_QUEUED;
		break;
	case VB2_BUF_STATE_IN_REQUEST:
		b->flags |= V4L2_BUF_FLAG_IN_REQUEST;
		break;
	case VB2_BUF_STATE_ERROR:
		b->flags |= V4L2_BUF_FLAG_ERROR;
		/* fall through */
	case VB2_BUF_STATE_DONE:
		b->flags |= V4L2_BUF_FLAG_DONE;
		break;
	case VB2_BUF_STATE_PREPARING:
	case VB2_BUF_STATE_DEQUEUED:
		/* nothing */
		break;
	}

	if ((vb->state == VB2_BUF_STATE_DEQUEUED ||
	     vb->state == VB2_BUF_STATE_IN_REQUEST) &&
	    vb->synced && vb->prepared)
		b->flags |= V4L2_BUF_FLAG_PREPARED;

	if (vb2_buffer_in_use(q, vb))
		b->flags |= V4L2_BUF_FLAG_MAPPED;
	if (vbuf->request_fd >= 0) {
		b->flags |= V4L2_BUF_FLAG_REQUEST_FD;
		b->request_fd = vbuf->request_fd;
	}
}