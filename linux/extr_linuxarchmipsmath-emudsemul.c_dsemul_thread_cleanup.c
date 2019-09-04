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
struct TYPE_2__ {int /*<<< orphan*/  bd_emu_frame; } ;
struct task_struct {scalar_t__ mm; TYPE_1__ thread; } ;

/* Variables and functions */
 int BD_EMUFRAME_NONE ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_emuframe (int,scalar_t__) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

bool dsemul_thread_cleanup(struct task_struct *tsk)
{
	int fr_idx;

	/* Clear any allocated frame, retrieving its index */
	fr_idx = atomic_xchg(&tsk->thread.bd_emu_frame, BD_EMUFRAME_NONE);

	/* If no frame was allocated, we're done */
	if (fr_idx == BD_EMUFRAME_NONE)
		return false;

	task_lock(tsk);

	/* Free the frame that this thread had allocated */
	if (tsk->mm)
		free_emuframe(fr_idx, tsk->mm);

	task_unlock(tsk);
	return true;
}