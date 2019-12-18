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
struct fimc_lite {int /*<<< orphan*/  slock; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fimc_lite_clear_event_counters(struct fimc_lite *fimc)
{
	unsigned long flags;

	spin_lock_irqsave(&fimc->slock, flags);
	memset(&fimc->events, 0, sizeof(fimc->events));
	spin_unlock_irqrestore(&fimc->slock, flags);
}