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
struct ispstat {int sbl_ovl_recover; TYPE_1__* isp; scalar_t__ recover_priv; int /*<<< orphan*/  buf_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap3isp_stat_sbl_overflow(struct ispstat *stat)
{
	unsigned long irqflags;

	spin_lock_irqsave(&stat->isp->stat_lock, irqflags);
	/*
	 * Due to a H3A hw issue which prevents the next buffer to start from
	 * the correct memory address, 2 buffers must be ignored.
	 */
	atomic_set(&stat->buf_err, 2);

	/*
	 * If more than one SBL overflow happen in a row, H3A module may access
	 * invalid memory region.
	 * stat->sbl_ovl_recover is set to tell to the driver to temporarily use
	 * a soft configuration which helps to avoid consecutive overflows.
	 */
	if (stat->recover_priv)
		stat->sbl_ovl_recover = 1;
	spin_unlock_irqrestore(&stat->isp->stat_lock, irqflags);
}