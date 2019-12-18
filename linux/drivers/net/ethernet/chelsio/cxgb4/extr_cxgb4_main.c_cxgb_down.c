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
struct adapter {int tid_release_task_busy; int /*<<< orphan*/  flags; int /*<<< orphan*/ * tid_release_head; int /*<<< orphan*/  db_drop_task; int /*<<< orphan*/  db_full_task; int /*<<< orphan*/  tid_release_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_FULL_INIT_DONE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t4_free_sge_resources (struct adapter*) ; 
 int /*<<< orphan*/  t4_sge_stop (struct adapter*) ; 

__attribute__((used)) static void cxgb_down(struct adapter *adapter)
{
	cancel_work_sync(&adapter->tid_release_task);
	cancel_work_sync(&adapter->db_full_task);
	cancel_work_sync(&adapter->db_drop_task);
	adapter->tid_release_task_busy = false;
	adapter->tid_release_head = NULL;

	t4_sge_stop(adapter);
	t4_free_sge_resources(adapter);

	adapter->flags &= ~CXGB4_FULL_INIT_DONE;
}