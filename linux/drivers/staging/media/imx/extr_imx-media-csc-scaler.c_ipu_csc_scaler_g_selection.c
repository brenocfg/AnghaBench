#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ipu_csc_scaler_q_data {TYPE_2__ cur_fmt; TYPE_1__ rect; } ;
struct ipu_csc_scaler_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct ipu_csc_scaler_ctx* fh_to_ctx (void*) ; 
 struct ipu_csc_scaler_q_data* get_q_data (struct ipu_csc_scaler_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipu_csc_scaler_g_selection(struct file *file, void *priv,
				      struct v4l2_selection *s)
{
	struct ipu_csc_scaler_ctx *ctx = fh_to_ctx(priv);
	struct ipu_csc_scaler_q_data *q_data;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP:
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		break;
	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		q_data = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_CAPTURE);
		break;
	default:
		return -EINVAL;
	}

	if (s->target == V4L2_SEL_TGT_CROP ||
	    s->target == V4L2_SEL_TGT_COMPOSE) {
		s->r = q_data->rect;
	} else {
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = q_data->cur_fmt.width;
		s->r.height = q_data->cur_fmt.height;
	}

	return 0;
}