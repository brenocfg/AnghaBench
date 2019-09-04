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
 int /*<<< orphan*/  TIF_SVE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sve_free (struct task_struct*) ; 
 int /*<<< orphan*/  test_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sve_free(struct task_struct *task)
{
	WARN_ON(test_tsk_thread_flag(task, TIF_SVE));

	__sve_free(task);
}