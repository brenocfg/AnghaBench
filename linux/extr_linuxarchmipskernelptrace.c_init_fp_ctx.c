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
struct TYPE_3__ {int /*<<< orphan*/  fpr; } ;
struct TYPE_4__ {TYPE_1__ fpu; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_stopped_child_used_math (struct task_struct*) ; 
 scalar_t__ tsk_used_math (struct task_struct*) ; 

__attribute__((used)) static void init_fp_ctx(struct task_struct *target)
{
	/* If FP has been used then the target already has context */
	if (tsk_used_math(target))
		return;

	/* Begin with data registers set to all 1s... */
	memset(&target->thread.fpu.fpr, ~0, sizeof(target->thread.fpu.fpr));

	/* FCSR has been preset by `mips_set_personality_nan'.  */

	/*
	 * Record that the target has "used" math, such that the context
	 * just initialised, and any modifications made by the caller,
	 * aren't discarded.
	 */
	set_stopped_child_used_math(target);
}