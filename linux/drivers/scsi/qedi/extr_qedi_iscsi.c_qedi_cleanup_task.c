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
struct iscsi_task {scalar_t__ state; int /*<<< orphan*/  dd_data; int /*<<< orphan*/  refcount; int /*<<< orphan*/  sc; } ;

/* Variables and functions */
 scalar_t__ ISCSI_TASK_PENDING ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_IO ; 
 int /*<<< orphan*/  qedi_iscsi_unmap_sg_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qedi_cleanup_task(struct iscsi_task *task)
{
	if (!task->sc || task->state == ISCSI_TASK_PENDING) {
		QEDI_INFO(NULL, QEDI_LOG_IO, "Returning ref_cnt=%d\n",
			  refcount_read(&task->refcount));
		return;
	}

	qedi_iscsi_unmap_sg_list(task->dd_data);
}