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
struct TYPE_4__ {int /*<<< orphan*/  pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_2__ fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct jpu_ctx {TYPE_1__ fh; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __jpu_try_fmt (struct jpu_ctx*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct jpu_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jpu_try_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct jpu_ctx *ctx = fh_to_ctx(priv);

	if (!v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		return -EINVAL;

	return __jpu_try_fmt(ctx, NULL, &f->fmt.pix_mp, f->type);
}