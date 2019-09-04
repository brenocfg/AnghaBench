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
struct TYPE_2__ {int /*<<< orphan*/ * lbr_exclusive; scalar_t__ lbr_pt_coexist; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_events ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 unsigned int x86_lbr_exclusive_pt ; 
 TYPE_1__ x86_pmu ; 

void x86_del_exclusive(unsigned int what)
{
	if (x86_pmu.lbr_pt_coexist && what == x86_lbr_exclusive_pt)
		return;

	atomic_dec(&x86_pmu.lbr_exclusive[what]);
	atomic_dec(&active_events);
}