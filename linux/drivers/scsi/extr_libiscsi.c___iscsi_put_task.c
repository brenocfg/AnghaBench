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
struct iscsi_task {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_free_task (struct iscsi_task*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void __iscsi_put_task(struct iscsi_task *task)
{
	if (refcount_dec_and_test(&task->refcount))
		iscsi_free_task(task);
}