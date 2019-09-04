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
struct fimc_dev {int state; int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int ST_CAPT_PEND ; 
 int ST_CAPT_RUN ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline bool fimc_capture_active(struct fimc_dev *fimc)
{
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&fimc->slock, flags);
	ret = !!(fimc->state & (1 << ST_CAPT_RUN) ||
		 fimc->state & (1 << ST_CAPT_PEND));
	spin_unlock_irqrestore(&fimc->slock, flags);
	return ret;
}