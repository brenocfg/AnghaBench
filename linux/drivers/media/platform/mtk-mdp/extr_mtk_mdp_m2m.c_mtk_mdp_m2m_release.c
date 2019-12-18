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
struct mtk_mdp_dev {int /*<<< orphan*/  lock; TYPE_1__* pdev; int /*<<< orphan*/  ctx_num; int /*<<< orphan*/  job_wq; } ;
struct mtk_mdp_ctx {int /*<<< orphan*/  id; int /*<<< orphan*/  list; int /*<<< orphan*/  vpu; int /*<<< orphan*/  fh; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  m2m_ctx; struct mtk_mdp_dev* mdp_dev; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct mtk_mdp_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mtk_mdp_ctx*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_mdp_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_vpu_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_mdp_m2m_release(struct file *file)
{
	struct mtk_mdp_ctx *ctx = fh_to_ctx(file->private_data);
	struct mtk_mdp_dev *mdp = ctx->mdp_dev;

	flush_workqueue(mdp->job_wq);
	mutex_lock(&mdp->lock);
	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	v4l2_ctrl_handler_free(&ctx->ctrl_handler);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	mtk_mdp_vpu_deinit(&ctx->vpu);
	mdp->ctx_num--;
	list_del_init(&ctx->list);

	mtk_mdp_dbg(0, "%s [%d]", dev_name(&mdp->pdev->dev), ctx->id);

	mutex_unlock(&mdp->lock);
	kfree(ctx);

	return 0;
}