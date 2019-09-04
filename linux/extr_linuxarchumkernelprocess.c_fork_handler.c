#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct TYPE_7__ {TYPE_1__ regs; int /*<<< orphan*/ * prev_sched; } ;
struct TYPE_9__ {TYPE_2__ thread; } ;
struct TYPE_8__ {int /*<<< orphan*/  aux_fp_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_switch_to (TYPE_4__*) ; 
 TYPE_4__* current ; 
 TYPE_3__* current_thread_info () ; 
 int /*<<< orphan*/  force_flush_all () ; 
 int /*<<< orphan*/  schedule_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  userspace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void fork_handler(void)
{
	force_flush_all();

	schedule_tail(current->thread.prev_sched);

	/*
	 * XXX: if interrupt_end() calls schedule, this call to
	 * arch_switch_to isn't needed. We could want to apply this to
	 * improve performance. -bb
	 */
	arch_switch_to(current);

	current->thread.prev_sched = NULL;

	userspace(&current->thread.regs.regs, current_thread_info()->aux_fp_regs);
}