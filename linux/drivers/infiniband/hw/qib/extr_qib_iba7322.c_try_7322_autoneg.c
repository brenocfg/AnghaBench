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
struct qib_pportdata {TYPE_1__* cpspec; int /*<<< orphan*/  lflags_lock; int /*<<< orphan*/  lflags; } ;
struct TYPE_2__ {int /*<<< orphan*/  autoneg_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIBL_IB_AUTONEG_INPROG ; 
 int /*<<< orphan*/  QIB_IB_DDR ; 
 int /*<<< orphan*/  ib_wq ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  qib_7322_mini_pcs_reset (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_autoneg_7322_send (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_7322_ibspeed_fast (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void try_7322_autoneg(struct qib_pportdata *ppd)
{
	unsigned long flags;

	spin_lock_irqsave(&ppd->lflags_lock, flags);
	ppd->lflags |= QIBL_IB_AUTONEG_INPROG;
	spin_unlock_irqrestore(&ppd->lflags_lock, flags);
	qib_autoneg_7322_send(ppd, 0);
	set_7322_ibspeed_fast(ppd, QIB_IB_DDR);
	qib_7322_mini_pcs_reset(ppd);
	/* 2 msec is minimum length of a poll cycle */
	queue_delayed_work(ib_wq, &ppd->cpspec->autoneg_work,
			   msecs_to_jiffies(2));
}