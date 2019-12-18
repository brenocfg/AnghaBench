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
struct vicodec_q_data {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  visible_height; int /*<<< orphan*/  visible_width; } ;
struct vicodec_ctx {scalar_t__ is_enc; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
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
 struct vicodec_ctx* file2ctx (struct file*) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_selection(struct file *file, void *priv,
			      struct v4l2_selection *s)
{
	struct vicodec_ctx *ctx = file2ctx(file);
	struct vicodec_q_data *q_data;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;
	/*
	 * encoder supports only cropping on the OUTPUT buffer
	 * decoder supports only composing on the CAPTURE buffer
	 */
	if (ctx->is_enc && s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		switch (s->target) {
		case V4L2_SEL_TGT_CROP:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->visible_width;
			s->r.height = q_data->visible_height;
			return 0;
		case V4L2_SEL_TGT_CROP_DEFAULT:
		case V4L2_SEL_TGT_CROP_BOUNDS:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->coded_width;
			s->r.height = q_data->coded_height;
			return 0;
		}
	} else if (!ctx->is_enc && s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		switch (s->target) {
		case V4L2_SEL_TGT_COMPOSE:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->visible_width;
			s->r.height = q_data->visible_height;
			return 0;
		case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		case V4L2_SEL_TGT_COMPOSE_BOUNDS:
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = q_data->coded_width;
			s->r.height = q_data->coded_height;
			return 0;
		}
	}
	return -EINVAL;
}