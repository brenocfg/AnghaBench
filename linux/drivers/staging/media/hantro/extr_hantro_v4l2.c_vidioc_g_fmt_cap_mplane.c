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
struct v4l2_pix_format_mplane {int dummy; } ;
struct TYPE_2__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {int /*<<< orphan*/  type; TYPE_1__ fmt; } ;
struct hantro_ctx {struct v4l2_pix_format_mplane dst_fmt; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct hantro_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  vpu_debug (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_fmt_cap_mplane(struct file *file, void *priv,
				   struct v4l2_format *f)
{
	struct v4l2_pix_format_mplane *pix_mp = &f->fmt.pix_mp;
	struct hantro_ctx *ctx = fh_to_ctx(priv);

	vpu_debug(4, "f->type = %d\n", f->type);

	*pix_mp = ctx->dst_fmt;

	return 0;
}