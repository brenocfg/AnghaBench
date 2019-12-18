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
struct delta_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct delta_ctx {int /*<<< orphan*/  name; scalar_t__ aborting; TYPE_1__ fh; struct delta_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 int v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int delta_job_ready(void *priv)
{
	struct delta_ctx *ctx = priv;
	struct delta_dev *delta = ctx->dev;
	int src_bufs = v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx);

	if (!src_bufs) {
		dev_dbg(delta->dev, "%s not ready: not enough video buffers.\n",
			ctx->name);
		return 0;
	}

	if (!v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx)) {
		dev_dbg(delta->dev, "%s not ready: not enough video capture buffers.\n",
			ctx->name);
		return 0;
	}

	if (ctx->aborting) {
		dev_dbg(delta->dev, "%s job not ready: aborting\n", ctx->name);
		return 0;
	}

	dev_dbg(delta->dev, "%s job ready\n", ctx->name);

	return 1;
}