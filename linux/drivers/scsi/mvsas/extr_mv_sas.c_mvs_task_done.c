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
struct sas_task {TYPE_1__* slow_task; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mvs_task_done(struct sas_task *task)
{
	if (!del_timer(&task->slow_task->timer))
		return;
	complete(&task->slow_task->completion);
}