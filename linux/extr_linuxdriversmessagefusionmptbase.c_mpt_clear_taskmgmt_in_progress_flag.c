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
struct TYPE_5__ {int /*<<< orphan*/  taskmgmt_lock; TYPE_1__* alt_ioc; scalar_t__ taskmgmt_quiesce_io; scalar_t__ taskmgmt_in_progress; } ;
struct TYPE_4__ {scalar_t__ taskmgmt_quiesce_io; scalar_t__ taskmgmt_in_progress; } ;
typedef  TYPE_2__ MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
mpt_clear_taskmgmt_in_progress_flag(MPT_ADAPTER *ioc)
{
	unsigned long	 flags;

	spin_lock_irqsave(&ioc->taskmgmt_lock, flags);
	ioc->taskmgmt_in_progress = 0;
	ioc->taskmgmt_quiesce_io = 0;
	if (ioc->alt_ioc) {
		ioc->alt_ioc->taskmgmt_in_progress = 0;
		ioc->alt_ioc->taskmgmt_quiesce_io = 0;
	}
	spin_unlock_irqrestore(&ioc->taskmgmt_lock, flags);
}