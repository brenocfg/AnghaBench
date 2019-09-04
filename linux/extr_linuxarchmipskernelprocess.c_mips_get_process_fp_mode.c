#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;

/* Variables and functions */
 int PR_FP_MODE_FR ; 
 int PR_FP_MODE_FRE ; 
 int /*<<< orphan*/  TIF_32BIT_FPREGS ; 
 int /*<<< orphan*/  TIF_HYBRID_FPREGS ; 
 scalar_t__ test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

int mips_get_process_fp_mode(struct task_struct *task)
{
	int value = 0;

	if (!test_tsk_thread_flag(task, TIF_32BIT_FPREGS))
		value |= PR_FP_MODE_FR;
	if (test_tsk_thread_flag(task, TIF_HYBRID_FPREGS))
		value |= PR_FP_MODE_FRE;

	return value;
}