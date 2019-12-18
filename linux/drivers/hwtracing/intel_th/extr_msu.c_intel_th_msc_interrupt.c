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
typedef  int /*<<< orphan*/  u32 ;
struct msc_window {int /*<<< orphan*/  sgt; } ;
struct msc {int /*<<< orphan*/  mbuf_priv; TYPE_1__* mbuf; int /*<<< orphan*/  work; struct msc_window* cur_win; scalar_t__ enabled; scalar_t__ msu_base; int /*<<< orphan*/  do_irq; scalar_t__ index; } ;
struct intel_th_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ready ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MSUSTS_MSC0BLAST ; 
 int /*<<< orphan*/  MSUSTS_MSC1BLAST ; 
 scalar_t__ REG_MSU_MSUSTS ; 
 int /*<<< orphan*/  WIN_INUSE ; 
 int /*<<< orphan*/  WIN_LOCKED ; 
 int /*<<< orphan*/  WIN_READY ; 
 struct msc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct msc_window* msc_next_window (struct msc_window*) ; 
 scalar_t__ msc_win_set_lockout (struct msc_window*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msc_win_switch (struct msc*) ; 
 int /*<<< orphan*/  msc_win_total_sz (struct msc_window*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t intel_th_msc_interrupt(struct intel_th_device *thdev)
{
	struct msc *msc = dev_get_drvdata(&thdev->dev);
	u32 msusts = ioread32(msc->msu_base + REG_MSU_MSUSTS);
	u32 mask = msc->index ? MSUSTS_MSC1BLAST : MSUSTS_MSC0BLAST;
	struct msc_window *win, *next_win;

	if (!msc->do_irq || !msc->mbuf)
		return IRQ_NONE;

	msusts &= mask;

	if (!msusts)
		return msc->enabled ? IRQ_HANDLED : IRQ_NONE;

	iowrite32(msusts, msc->msu_base + REG_MSU_MSUSTS);

	if (!msc->enabled)
		return IRQ_NONE;

	/* grab the window before we do the switch */
	win = msc->cur_win;
	if (!win)
		return IRQ_HANDLED;
	next_win = msc_next_window(win);
	if (!next_win)
		return IRQ_HANDLED;

	/* next window: if READY, proceed, if LOCKED, stop the trace */
	if (msc_win_set_lockout(next_win, WIN_READY, WIN_INUSE)) {
		schedule_work(&msc->work);
		return IRQ_HANDLED;
	}

	/* current window: INUSE -> LOCKED */
	msc_win_set_lockout(win, WIN_INUSE, WIN_LOCKED);

	msc_win_switch(msc);

	if (msc->mbuf && msc->mbuf->ready)
		msc->mbuf->ready(msc->mbuf_priv, win->sgt,
				 msc_win_total_sz(win));

	return IRQ_HANDLED;
}