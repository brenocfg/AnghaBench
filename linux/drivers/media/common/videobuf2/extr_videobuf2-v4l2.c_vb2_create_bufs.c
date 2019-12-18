#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int /*<<< orphan*/  num_buffers; } ;
struct TYPE_15__ {unsigned int buffersize; } ;
struct TYPE_14__ {unsigned int buffersize; } ;
struct TYPE_13__ {unsigned int io_size; } ;
struct TYPE_12__ {unsigned int samples_per_line; unsigned int* count; } ;
struct TYPE_11__ {unsigned int sizeimage; } ;
struct TYPE_10__ {unsigned int num_planes; TYPE_1__* plane_fmt; } ;
struct TYPE_16__ {TYPE_7__ meta; TYPE_6__ sdr; TYPE_5__ sliced; TYPE_4__ vbi; TYPE_3__ pix; TYPE_2__ pix_mp; } ;
struct v4l2_format {int type; TYPE_8__ fmt; } ;
struct v4l2_create_buffers {scalar_t__ count; int /*<<< orphan*/  memory; int /*<<< orphan*/  index; int /*<<< orphan*/  capabilities; struct v4l2_format format; } ;
struct TYPE_9__ {unsigned int sizeimage; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  V4L2_BUF_TYPE_META_CAPTURE 139 
#define  V4L2_BUF_TYPE_META_OUTPUT 138 
#define  V4L2_BUF_TYPE_SDR_CAPTURE 137 
#define  V4L2_BUF_TYPE_SDR_OUTPUT 136 
#define  V4L2_BUF_TYPE_SLICED_VBI_CAPTURE 135 
#define  V4L2_BUF_TYPE_SLICED_VBI_OUTPUT 134 
#define  V4L2_BUF_TYPE_VBI_CAPTURE 133 
#define  V4L2_BUF_TYPE_VBI_OUTPUT 132 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 131 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 130 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 129 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 128 
 int VIDEO_MAX_PLANES ; 
 int /*<<< orphan*/  fill_buf_caps (struct vb2_queue*,int /*<<< orphan*/ *) ; 
 int vb2_core_create_bufs (struct vb2_queue*,int /*<<< orphan*/ ,scalar_t__*,unsigned int,unsigned int*) ; 
 int vb2_verify_memory_type (struct vb2_queue*,int /*<<< orphan*/ ,int) ; 

int vb2_create_bufs(struct vb2_queue *q, struct v4l2_create_buffers *create)
{
	unsigned requested_planes = 1;
	unsigned requested_sizes[VIDEO_MAX_PLANES];
	struct v4l2_format *f = &create->format;
	int ret = vb2_verify_memory_type(q, create->memory, f->type);
	unsigned i;

	fill_buf_caps(q, &create->capabilities);
	create->index = q->num_buffers;
	if (create->count == 0)
		return ret != -EBUSY ? ret : 0;

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		requested_planes = f->fmt.pix_mp.num_planes;
		if (requested_planes == 0 ||
		    requested_planes > VIDEO_MAX_PLANES)
			return -EINVAL;
		for (i = 0; i < requested_planes; i++)
			requested_sizes[i] =
				f->fmt.pix_mp.plane_fmt[i].sizeimage;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		requested_sizes[0] = f->fmt.pix.sizeimage;
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.vbi.samples_per_line *
			(f->fmt.vbi.count[0] + f->fmt.vbi.count[1]);
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.sliced.io_size;
		break;
	case V4L2_BUF_TYPE_SDR_CAPTURE:
	case V4L2_BUF_TYPE_SDR_OUTPUT:
		requested_sizes[0] = f->fmt.sdr.buffersize;
		break;
	case V4L2_BUF_TYPE_META_CAPTURE:
	case V4L2_BUF_TYPE_META_OUTPUT:
		requested_sizes[0] = f->fmt.meta.buffersize;
		break;
	default:
		return -EINVAL;
	}
	for (i = 0; i < requested_planes; i++)
		if (requested_sizes[i] == 0)
			return -EINVAL;
	return ret ? ret : vb2_core_create_bufs(q, create->memory,
		&create->count, requested_planes, requested_sizes);
}