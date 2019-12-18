#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  private_data; } ;
struct coda_dev {int /*<<< orphan*/  ida; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk_per; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  workqueue; } ;
struct TYPE_9__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {scalar_t__ inst_type; int /*<<< orphan*/  debugfs_entry; TYPE_3__* ops; int /*<<< orphan*/  idx; TYPE_4__ fh; int /*<<< orphan*/  ctrls; int /*<<< orphan*/  workbuf; TYPE_2__* dev; int /*<<< orphan*/  seq_end_work; scalar_t__ vdoa; scalar_t__ use_bit; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* release ) (struct coda_ctx*) ;scalar_t__ seq_end_work; } ;
struct TYPE_7__ {TYPE_1__* devtype; } ;
struct TYPE_6__ {scalar_t__ product; } ;

/* Variables and functions */
 scalar_t__ CODA_DX6 ; 
 scalar_t__ CODA_INST_DECODER ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_bit_stream_end_flag (struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_dbg (int,struct coda_ctx*,char*,struct coda_ctx*) ; 
 int /*<<< orphan*/  coda_free_aux_buf (struct coda_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct coda_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct coda_ctx*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct coda_ctx*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdoa_context_destroy (scalar_t__) ; 
 struct coda_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int coda_release(struct file *file)
{
	struct coda_dev *dev = video_drvdata(file);
	struct coda_ctx *ctx = fh_to_ctx(file->private_data);

	coda_dbg(1, ctx, "release instance (%p)\n", ctx);

	if (ctx->inst_type == CODA_INST_DECODER && ctx->use_bit)
		coda_bit_stream_end_flag(ctx);

	/* If this instance is running, call .job_abort and wait for it to end */
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);

	if (ctx->vdoa)
		vdoa_context_destroy(ctx->vdoa);

	/* In case the instance was not running, we still need to call SEQ_END */
	if (ctx->ops->seq_end_work) {
		queue_work(dev->workqueue, &ctx->seq_end_work);
		flush_work(&ctx->seq_end_work);
	}

	if (ctx->dev->devtype->product == CODA_DX6)
		coda_free_aux_buf(dev, &ctx->workbuf);

	v4l2_ctrl_handler_free(&ctx->ctrls);
	clk_disable_unprepare(dev->clk_ahb);
	clk_disable_unprepare(dev->clk_per);
	pm_runtime_put_sync(dev->dev);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	ida_free(&dev->ida, ctx->idx);
	if (ctx->ops->release)
		ctx->ops->release(ctx);
	debugfs_remove_recursive(ctx->debugfs_entry);
	kfree(ctx);

	return 0;
}