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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  left; int /*<<< orphan*/  top; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct mtk_vcodec_ctx {int dummy; } ;
struct mtk_q_data {int /*<<< orphan*/  visible_height; int /*<<< orphan*/  visible_width; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct mtk_vcodec_ctx* fh_to_ctx (void*) ; 
 struct mtk_q_data* mtk_venc_get_q_data (struct mtk_vcodec_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_venc_g_selection(struct file *file, void *priv,
				     struct v4l2_selection *s)
{
	struct mtk_vcodec_ctx *ctx = fh_to_ctx(priv);
	struct mtk_q_data *q_data;

	if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	q_data = mtk_venc_get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		s->r.top = 0;
		s->r.left = 0;
		s->r.width = q_data->coded_width;
		s->r.height = q_data->coded_height;
		break;
	case V4L2_SEL_TGT_CROP:
		s->r.top = 0;
		s->r.left = 0;
		s->r.width = q_data->visible_width;
		s->r.height = q_data->visible_height;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}