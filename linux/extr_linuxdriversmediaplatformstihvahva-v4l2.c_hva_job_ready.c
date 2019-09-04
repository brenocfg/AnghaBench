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
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct hva_ctx {int /*<<< orphan*/  name; scalar_t__ aborting; TYPE_1__ fh; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* ctx_to_dev (struct hva_ctx*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_num_dst_bufs_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_num_src_bufs_ready (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hva_job_ready(void *priv)
{
	struct hva_ctx *ctx = priv;
	struct device *dev = ctx_to_dev(ctx);

	if (!v4l2_m2m_num_src_bufs_ready(ctx->fh.m2m_ctx)) {
		dev_dbg(dev, "%s job not ready: no frame buffers\n",
			ctx->name);
		return 0;
	}

	if (!v4l2_m2m_num_dst_bufs_ready(ctx->fh.m2m_ctx)) {
		dev_dbg(dev, "%s job not ready: no stream buffers\n",
			ctx->name);
		return 0;
	}

	if (ctx->aborting) {
		dev_dbg(dev, "%s job not ready: aborting\n", ctx->name);
		return 0;
	}

	return 1;
}