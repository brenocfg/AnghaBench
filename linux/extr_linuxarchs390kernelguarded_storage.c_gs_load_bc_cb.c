#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct gs_cb {int dummy; } ;
struct TYPE_3__ {struct gs_cb* gs_cb; struct gs_cb* gs_bc_cb; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_GUARDED_STORAGE ; 
 int /*<<< orphan*/  __ctl_set_bit (int,int) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (struct gs_cb*) ; 
 int /*<<< orphan*/  load_gs_cb (struct gs_cb*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void gs_load_bc_cb(struct pt_regs *regs)
{
	struct gs_cb *gs_cb;

	preempt_disable();
	clear_thread_flag(TIF_GUARDED_STORAGE);
	gs_cb = current->thread.gs_bc_cb;
	if (gs_cb) {
		kfree(current->thread.gs_cb);
		current->thread.gs_bc_cb = NULL;
		__ctl_set_bit(2, 4);
		load_gs_cb(gs_cb);
		current->thread.gs_cb = gs_cb;
	}
	preempt_enable();
}