#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct ispstat {scalar_t__ state; int update; TYPE_3__* isp; TYPE_2__ subdev; int /*<<< orphan*/  buf_err; int /*<<< orphan*/  active_buf; int /*<<< orphan*/ * priv; TYPE_1__* ops; scalar_t__ buf_alloc_size; int /*<<< orphan*/  buf_processing; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat_lock; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* setup_regs ) (struct ispstat*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ ISPSTAT_ENABLING ; 
 int /*<<< orphan*/  IS_H3A (struct ispstat*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_insert_magic (struct ispstat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_stat_buf_next (struct ispstat*) ; 
 int /*<<< orphan*/  isp_stat_pcr_enable (struct ispstat*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct ispstat*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isp_stat_try_enable(struct ispstat *stat)
{
	unsigned long irqflags;

	if (stat->priv == NULL)
		/* driver wasn't initialised */
		return;

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	if (stat->state == ISPSTAT_ENABLING && !stat->buf_processing &&
	    stat->buf_alloc_size) {
		/*
		 * Userspace's requested to enable the engine but it wasn't yet.
		 * Let's do that now.
		 */
		stat->update = 1;
		isp_stat_buf_next(stat);
		stat->ops->setup_regs(stat, stat->priv);
		isp_stat_buf_insert_magic(stat, stat->active_buf);

		/*
		 * H3A module has some hw issues which forces the driver to
		 * ignore next buffers even if it was disabled in the meantime.
		 * On the other hand, Histogram shouldn't ignore buffers anymore
		 * if it's being enabled.
		 */
		if (!IS_H3A(stat))
			atomic_set(&stat->buf_err, 0);

		isp_stat_pcr_enable(stat, 1);
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
		dev_dbg(stat->isp->dev, "%s: module is enabled.\n",
			stat->subdev.name);
	} else {
		spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
	}
}