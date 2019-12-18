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
struct TYPE_2__ {int /*<<< orphan*/ * stat1; } ;

/* Variables and functions */
 unsigned int __raw_readl (int /*<<< orphan*/ *) ; 
 TYPE_1__* qmgr_regs ; 

__attribute__((used)) static int __qmgr_get_stat1(unsigned int queue)
{
	return (__raw_readl(&qmgr_regs->stat1[queue >> 3])
		>> ((queue & 7) << 2)) & 0xF;
}