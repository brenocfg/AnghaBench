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
struct ispstat {TYPE_1__* isp; int /*<<< orphan*/ * locked_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp_stat_buf_sync_for_device (struct ispstat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void isp_stat_buf_release(struct ispstat *stat)
{
	unsigned long flags;

	isp_stat_buf_sync_for_device(stat, stat->locked_buf);
	spin_lock_irqsave(&stat->isp->stat_lock, flags);
	stat->locked_buf = NULL;
	spin_unlock_irqrestore(&stat->isp->stat_lock, flags);
}