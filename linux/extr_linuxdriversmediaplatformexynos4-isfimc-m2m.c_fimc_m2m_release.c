#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ refcnt; } ;
struct fimc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__ m2m; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct fimc_ctx {TYPE_2__ fh; struct fimc_dev* fimc_dev; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_M2M_RUN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct fimc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_ctrls_delete (struct fimc_ctx*) ; 
 int /*<<< orphan*/  kfree (struct fimc_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_fh_exit (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_m2m_release(struct file *file)
{
	struct fimc_ctx *ctx = fh_to_ctx(file->private_data);
	struct fimc_dev *fimc = ctx->fimc_dev;

	dbg("pid: %d, state: 0x%lx, refcnt= %d",
		task_pid_nr(current), fimc->state, fimc->m2m.refcnt);

	mutex_lock(&fimc->lock);

	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	fimc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);

	if (--fimc->m2m.refcnt <= 0)
		clear_bit(ST_M2M_RUN, &fimc->state);
	kfree(ctx);

	mutex_unlock(&fimc->lock);
	return 0;
}