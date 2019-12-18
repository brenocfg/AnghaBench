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
struct TYPE_3__ {int /*<<< orphan*/  field; } ;
struct fdp1_q_data {TYPE_1__ format; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fdp1_ctx {int /*<<< orphan*/  fdp1; TYPE_2__ fh; struct fdp1_q_data out_q; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 int v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fdp1_m2m_job_ready(void *priv)
{
	struct fdp1_ctx *ctx = priv;
	struct fdp1_q_data *src_q_data = &ctx->out_q;
	int srcbufs = 1;
	int dstbufs = 1;

	dprintk(ctx->fdp1, "+ Src: %d : Dst: %d\n",
		v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx),
		v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx));

	/* One output buffer is required for each field */
	if (V4L2_FIELD_HAS_BOTH(src_q_data->format.field))
		dstbufs = 2;

	if (v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx) < srcbufs
	    || v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx) < dstbufs) {
		dprintk(ctx->fdp1, "Not enough buffers available\n");
		return 0;
	}

	return 1;
}