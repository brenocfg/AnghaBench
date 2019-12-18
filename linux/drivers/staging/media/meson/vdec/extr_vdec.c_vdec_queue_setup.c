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
typedef  unsigned int u32 ;
struct vb2_queue {int type; } ;
struct device {int dummy; } ;
struct amvdec_session {int /*<<< orphan*/  pixfmt_cap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE 131 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE 130 
#define  V4L2_PIX_FMT_NV12M 129 
#define  V4L2_PIX_FMT_YUV420M 128 
 unsigned int amvdec_get_output_size (struct amvdec_session*) ; 
 int /*<<< orphan*/  process_num_buffers (struct vb2_queue*,struct amvdec_session*,unsigned int*,int) ; 
 struct amvdec_session* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int vdec_queue_setup(struct vb2_queue *q, unsigned int *num_buffers,
			    unsigned int *num_planes, unsigned int sizes[],
			    struct device *alloc_devs[])
{
	struct amvdec_session *sess = vb2_get_drv_priv(q);
	u32 output_size = amvdec_get_output_size(sess);

	if (*num_planes) {
		switch (q->type) {
		case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
			if (*num_planes != 1 || sizes[0] < output_size)
				return -EINVAL;
			break;
		case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
			switch (sess->pixfmt_cap) {
			case V4L2_PIX_FMT_NV12M:
				if (*num_planes != 2 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 2)
					return -EINVAL;
				break;
			case V4L2_PIX_FMT_YUV420M:
				if (*num_planes != 3 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 4 ||
				    sizes[2] < output_size / 4)
					return -EINVAL;
				break;
			default:
				return -EINVAL;
			}

			process_num_buffers(q, sess, num_buffers, false);
			break;
		}

		return 0;
	}

	switch (q->type) {
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		sizes[0] = amvdec_get_output_size(sess);
		*num_planes = 1;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
		switch (sess->pixfmt_cap) {
		case V4L2_PIX_FMT_NV12M:
			sizes[0] = output_size;
			sizes[1] = output_size / 2;
			*num_planes = 2;
			break;
		case V4L2_PIX_FMT_YUV420M:
			sizes[0] = output_size;
			sizes[1] = output_size / 4;
			sizes[2] = output_size / 4;
			*num_planes = 3;
			break;
		default:
			return -EINVAL;
		}

		process_num_buffers(q, sess, num_buffers, true);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}