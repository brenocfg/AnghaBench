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
struct v4l2_format {TYPE_2__ fmt; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct fdp1_q_data {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {TYPE_1__ fh; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fdp1_ctx* fh_to_ctx (void*) ; 
 struct fdp1_q_data* get_q_data (struct fdp1_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_get_vq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdp1_g_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct fdp1_q_data *q_data;
	struct fdp1_ctx *ctx = fh_to_ctx(priv);

	if (!v4l2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		return -EINVAL;

	q_data = get_q_data(ctx, f->type);
	f->fmt.pix_mp = q_data->format;

	return 0;
}