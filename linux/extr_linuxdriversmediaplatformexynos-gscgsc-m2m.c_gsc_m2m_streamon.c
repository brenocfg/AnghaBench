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
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GSC_DST_FMT ; 
 int /*<<< orphan*/  GSC_SRC_FMT ; 
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int) ; 
 struct gsc_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  gsc_ctx_state_is_set (int /*<<< orphan*/ ,struct gsc_ctx*) ; 
 int v4l2_m2m_streamon (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gsc_m2m_streamon(struct file *file, void *fh,
			   enum v4l2_buf_type type)
{
	struct gsc_ctx *ctx = fh_to_ctx(fh);

	/* The source and target color format need to be set */
	if (V4L2_TYPE_IS_OUTPUT(type)) {
		if (!gsc_ctx_state_is_set(GSC_SRC_FMT, ctx))
			return -EINVAL;
	} else if (!gsc_ctx_state_is_set(GSC_DST_FMT, ctx)) {
		return -EINVAL;
	}

	return v4l2_m2m_streamon(file, ctx->m2m_ctx, type);
}