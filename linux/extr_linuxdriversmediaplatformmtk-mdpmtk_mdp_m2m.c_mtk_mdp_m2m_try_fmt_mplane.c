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
struct v4l2_format {int dummy; } ;
struct mtk_mdp_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mtk_mdp_ctx* fh_to_ctx (void*) ; 
 int /*<<< orphan*/  mtk_mdp_try_fmt_mplane (struct mtk_mdp_ctx*,struct v4l2_format*) ; 

__attribute__((used)) static int mtk_mdp_m2m_try_fmt_mplane(struct file *file, void *fh,
				      struct v4l2_format *f)
{
	struct mtk_mdp_ctx *ctx = fh_to_ctx(fh);

	if (!mtk_mdp_try_fmt_mplane(ctx, f))
		return -EINVAL;
	return 0;
}