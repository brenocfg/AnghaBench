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
struct v4l2_fmtdesc {int dummy; } ;
struct jpu_ctx {scalar_t__ encoder; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  JPU_DEC_CAPTURE ; 
 int /*<<< orphan*/  JPU_ENC_CAPTURE ; 
 struct jpu_ctx* fh_to_ctx (void*) ; 
 int jpu_enum_fmt (struct v4l2_fmtdesc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpu_enum_fmt_cap(struct file *file, void *priv,
			    struct v4l2_fmtdesc *f)
{
	struct jpu_ctx *ctx = fh_to_ctx(priv);

	return jpu_enum_fmt(f, ctx->encoder ? JPU_ENC_CAPTURE :
			    JPU_DEC_CAPTURE);
}