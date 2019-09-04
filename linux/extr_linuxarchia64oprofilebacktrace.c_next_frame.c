#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pfs_loc; int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_3__ frame; int /*<<< orphan*/ * prev_pfs_loc; TYPE_1__* regs; } ;
typedef  TYPE_2__ ia64_backtrace_t ;
struct TYPE_5__ {int /*<<< orphan*/  ar_pfs; } ;

/* Variables and functions */
 scalar_t__ in_ivt_code (int /*<<< orphan*/ ) ; 
 scalar_t__ unw_unwind (TYPE_3__*) ; 

__attribute__((used)) static __inline__ int next_frame(ia64_backtrace_t *bt)
{
	/*
	 * Avoid unsightly console message from unw_unwind() when attempting
	 * to unwind through the Interrupt Vector Table which has no unwind
	 * information.
	 */
	if (in_ivt_code(bt->frame.ip))
		return 0;

	/*
	 * WAR for spinlock contention from leaf functions.  ia64_spinlock_contention_pre3_4
	 * has ar.pfs == r0.  Leaf functions do not modify ar.pfs so ar.pfs remains
	 * as 0, stopping the backtrace.  Record the previous ar.pfs when the current
	 * IP is in ia64_spinlock_contention_pre3_4 then unwind, if pfs_loc has not changed
	 * after unwind then use pt_regs.ar_pfs which is where the real ar.pfs is for
	 * leaf functions.
	 */
	if (bt->prev_pfs_loc && bt->regs && bt->frame.pfs_loc == bt->prev_pfs_loc)
		bt->frame.pfs_loc = &bt->regs->ar_pfs;
	bt->prev_pfs_loc = NULL;

	return unw_unwind(&bt->frame) == 0;
}