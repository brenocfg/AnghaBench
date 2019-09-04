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
struct TYPE_2__ {scalar_t__ refcnt; } ;
struct gsc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__ m2m; } ;
struct gsc_ctx {int /*<<< orphan*/  fh; int /*<<< orphan*/  m2m_ctx; struct gsc_dev* gsc_dev; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_M2M_OPEN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct gsc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_ctrls_delete (struct gsc_ctx*) ; 
 int /*<<< orphan*/  kfree (struct gsc_ctx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_ctx_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gsc_m2m_release(struct file *file)
{
	struct gsc_ctx *ctx = fh_to_ctx(file->private_data);
	struct gsc_dev *gsc = ctx->gsc_dev;

	pr_debug("pid: %d, state: 0x%lx, refcnt= %d",
		task_pid_nr(current), gsc->state, gsc->m2m.refcnt);

	mutex_lock(&gsc->lock);

	v4l2_m2m_ctx_release(ctx->m2m_ctx);
	gsc_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);

	if (--gsc->m2m.refcnt <= 0)
		clear_bit(ST_M2M_OPEN, &gsc->state);
	kfree(ctx);

	mutex_unlock(&gsc->lock);
	return 0;
}