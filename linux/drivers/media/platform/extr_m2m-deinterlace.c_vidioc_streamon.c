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
struct file {int dummy; } ;
struct deinterlace_q_data {int field; TYPE_1__* fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct deinterlace_ctx {TYPE_3__ fh; TYPE_2__* dev; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_5__ {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_FIELD_INTERLACED_BT ; 
 int V4L2_FIELD_INTERLACED_TB ; 
 int V4L2_FIELD_NONE ; 
#define  V4L2_FIELD_SEQ_BT 129 
#define  V4L2_FIELD_SEQ_TB 128 
 struct deinterlace_q_data* get_q_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 
 int v4l2_m2m_streamon (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv,
			   enum v4l2_buf_type type)
{
	struct deinterlace_q_data *s_q_data, *d_q_data;
	struct deinterlace_ctx *ctx = priv;

	s_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_OUTPUT);
	d_q_data = get_q_data(V4L2_BUF_TYPE_VIDEO_CAPTURE);

	/* Check that src and dst queues have the same pix format */
	if (s_q_data->fmt->fourcc != d_q_data->fmt->fourcc) {
		v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst formats don't match.\n");
		return -EINVAL;
	}

	/* Check that input and output deinterlacing types are compatible */
	switch (s_q_data->field) {
	case V4L2_FIELD_SEQ_BT:
		if (d_q_data->field != V4L2_FIELD_NONE &&
			d_q_data->field != V4L2_FIELD_INTERLACED_BT) {
			v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst field conversion [(%d)->(%d)] not supported.\n",
				s_q_data->field, d_q_data->field);
			return -EINVAL;
		}
		break;
	case V4L2_FIELD_SEQ_TB:
		if (d_q_data->field != V4L2_FIELD_NONE &&
			d_q_data->field != V4L2_FIELD_INTERLACED_TB) {
			v4l2_err(&ctx->dev->v4l2_dev,
			 "src and dst field conversion [(%d)->(%d)] not supported.\n",
				s_q_data->field, d_q_data->field);
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
}