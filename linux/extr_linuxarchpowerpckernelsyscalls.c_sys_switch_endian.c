#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__* regs; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;
struct TYPE_4__ {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_LE ; 
 int /*<<< orphan*/  _TIF_RESTOREALL ; 
 TYPE_3__* current ; 
 struct thread_info* current_thread_info () ; 

long sys_switch_endian(void)
{
	struct thread_info *ti;

	current->thread.regs->msr ^= MSR_LE;

	/*
	 * Set TIF_RESTOREALL so that r3 isn't clobbered on return to
	 * userspace. That also has the effect of restoring the non-volatile
	 * GPRs, so we saved them on the way in here.
	 */
	ti = current_thread_info();
	ti->flags |= _TIF_RESTOREALL;

	return 0;
}