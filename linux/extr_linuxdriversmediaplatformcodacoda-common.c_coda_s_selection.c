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
struct TYPE_2__ {void* height; void* width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {scalar_t__ target; int flags; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct coda_q_data {TYPE_1__ rect; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct coda_ctx {scalar_t__ inst_type; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_ENCODER ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_SEL_FLAG_LE ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 void* clamp (void*,unsigned int,int /*<<< orphan*/ ) ; 
 int coda_g_selection (struct file*,void*,struct v4l2_selection*) ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 void* round_down (void*,int) ; 
 void* round_up (void*,int) ; 

__attribute__((used)) static int coda_s_selection(struct file *file, void *fh,
			    struct v4l2_selection *s)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);
	struct coda_q_data *q_data;

	if (ctx->inst_type == CODA_INST_ENCODER &&
	    s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->target == V4L2_SEL_TGT_CROP) {
		q_data = get_q_data(ctx, s->type);
		if (!q_data)
			return -EINVAL;

		s->r.left = 0;
		s->r.top = 0;
		s->r.width = clamp(s->r.width, 2U, q_data->width);
		s->r.height = clamp(s->r.height, 2U, q_data->height);

		if (s->flags & V4L2_SEL_FLAG_LE) {
			s->r.width = round_up(s->r.width, 2);
			s->r.height = round_up(s->r.height, 2);
		} else {
			s->r.width = round_down(s->r.width, 2);
			s->r.height = round_down(s->r.height, 2);
		}

		q_data->rect = s->r;

		return 0;
	}

	return coda_g_selection(file, fh, s);
}