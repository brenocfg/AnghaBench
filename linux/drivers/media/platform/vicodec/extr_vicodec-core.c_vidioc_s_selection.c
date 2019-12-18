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
struct vicodec_q_data {void* visible_height; int /*<<< orphan*/  coded_height; void* visible_width; int /*<<< orphan*/  coded_width; } ;
struct vicodec_ctx {int /*<<< orphan*/  is_enc; } ;
struct TYPE_2__ {void* height; void* width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {scalar_t__ target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIN_HEIGHT ; 
 int /*<<< orphan*/  MIN_WIDTH ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 void* clamp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vicodec_ctx* file2ctx (struct file*) ; 
 struct vicodec_q_data* get_q_data (struct vicodec_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_selection(struct file *file, void *priv,
			      struct v4l2_selection *s)
{
	struct vicodec_ctx *ctx = file2ctx(file);
	struct vicodec_q_data *q_data;

	if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;

	if (!ctx->is_enc || s->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	s->r.left = 0;
	s->r.top = 0;
	q_data->visible_width = clamp(s->r.width, MIN_WIDTH,
				      q_data->coded_width);
	s->r.width = q_data->visible_width;
	q_data->visible_height = clamp(s->r.height, MIN_HEIGHT,
				       q_data->coded_height);
	s->r.height = q_data->visible_height;
	return 0;
}