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
struct s5p_mfc_dev {scalar_t__ curr_ctx; scalar_t__ num_inst; int /*<<< orphan*/  mfc_mutex; int /*<<< orphan*/ ** ctx; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  hw_lock; } ;
struct s5p_mfc_ctx {scalar_t__ state; scalar_t__ num; int /*<<< orphan*/  fh; int /*<<< orphan*/  vq_dst; int /*<<< orphan*/  vq_src; struct s5p_mfc_dev* dev; } ;
struct file {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 scalar_t__ MFCINST_FREE ; 
 scalar_t__ MFCINST_INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_work_bit_irqsave (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  mfc_debug (int,char*) ; 
 int /*<<< orphan*/  mfc_debug_enter () ; 
 int /*<<< orphan*/  mfc_debug_leave () ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 int /*<<< orphan*/  s5p_mfc_close_mfc_inst (struct s5p_mfc_dev*,struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_dec_ctrls_delete (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_deinit_hw (struct s5p_mfc_dev*) ; 
 scalar_t__ s5p_mfc_power_off () ; 
 int /*<<< orphan*/  v4l2_fh_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_fh_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s5p_mfc_release(struct file *file)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(file->private_data);
	struct s5p_mfc_dev *dev = ctx->dev;

	/* if dev is null, do cleanup that doesn't need dev */
	mfc_debug_enter();
	if (dev)
		mutex_lock(&dev->mfc_mutex);
	vb2_queue_release(&ctx->vq_src);
	vb2_queue_release(&ctx->vq_dst);
	if (dev) {
		s5p_mfc_clock_on();

		/* Mark context as idle */
		clear_work_bit_irqsave(ctx);
		/*
		 * If instance was initialised and not yet freed,
		 * return instance and free resources
		*/
		if (ctx->state != MFCINST_FREE && ctx->state != MFCINST_INIT) {
			mfc_debug(2, "Has to free instance\n");
			s5p_mfc_close_mfc_inst(dev, ctx);
		}
		/* hardware locking scheme */
		if (dev->curr_ctx == ctx->num)
			clear_bit(0, &dev->hw_lock);
		dev->num_inst--;
		if (dev->num_inst == 0) {
			mfc_debug(2, "Last instance\n");
			s5p_mfc_deinit_hw(dev);
			del_timer_sync(&dev->watchdog_timer);
			s5p_mfc_clock_off();
			if (s5p_mfc_power_off() < 0)
				mfc_err("Power off failed\n");
		} else {
			mfc_debug(2, "Shutting down clock\n");
			s5p_mfc_clock_off();
		}
	}
	if (dev)
		dev->ctx[ctx->num] = NULL;
	s5p_mfc_dec_ctrls_delete(ctx);
	v4l2_fh_del(&ctx->fh);
	/* vdev is gone if dev is null */
	if (dev)
		v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
	mfc_debug_leave();
	if (dev)
		mutex_unlock(&dev->mfc_mutex);

	return 0;
}