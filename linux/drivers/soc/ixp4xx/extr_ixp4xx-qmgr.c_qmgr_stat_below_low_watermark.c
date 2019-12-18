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
struct TYPE_2__ {int /*<<< orphan*/  statne_h; } ;

/* Variables and functions */
 unsigned int HALF_QUEUES ; 
 int QUEUE_STAT1_NEARLY_EMPTY ; 
 int __qmgr_get_stat1 (unsigned int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ *) ; 
 TYPE_1__* qmgr_regs ; 

int qmgr_stat_below_low_watermark(unsigned int queue)
{
	if (queue >= HALF_QUEUES)
		return (__raw_readl(&qmgr_regs->statne_h) >>
			(queue - HALF_QUEUES)) & 0x01;
	return __qmgr_get_stat1(queue) & QUEUE_STAT1_NEARLY_EMPTY;
}