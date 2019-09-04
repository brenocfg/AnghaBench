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
struct v4l2_format {int /*<<< orphan*/  type; } ;
struct fimc_frame {int dummy; } ;
struct fimc_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct fimc_frame*) ; 
 int PTR_ERR (struct fimc_frame*) ; 
 int /*<<< orphan*/  __fimc_get_format (struct fimc_frame*,struct v4l2_format*) ; 
 struct fimc_frame* ctx_get_frame (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 struct fimc_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int fimc_m2m_g_fmt_mplane(struct file *file, void *fh,
				 struct v4l2_format *f)
{
	struct fimc_ctx *ctx = fh_to_ctx(fh);
	struct fimc_frame *frame = ctx_get_frame(ctx, f->type);

	if (IS_ERR(frame))
		return PTR_ERR(frame);

	__fimc_get_format(frame, f);
	return 0;
}