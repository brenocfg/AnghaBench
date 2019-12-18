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
struct TYPE_2__ {int /*<<< orphan*/ * stat2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int HALF_QUEUES ; 
 unsigned int __raw_readl (int /*<<< orphan*/ *) ; 
 TYPE_1__* qmgr_regs ; 

__attribute__((used)) static int __qmgr_get_stat2(unsigned int queue)
{
	BUG_ON(queue >= HALF_QUEUES);
	return (__raw_readl(&qmgr_regs->stat2[queue >> 4])
		>> ((queue & 0xF) << 1)) & 0x3;
}