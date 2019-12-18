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
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct hinic_eq_work {int /*<<< orphan*/  work; } ;
struct hinic_eq {scalar_t__ type; int /*<<< orphan*/  ceq_tasklet; struct hinic_eq_work aeq_work; struct msix_entry msix_entry; } ;

/* Variables and functions */
 scalar_t__ HINIC_AEQ ; 
 scalar_t__ HINIC_CEQ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_eq_pages (struct hinic_eq*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hinic_eq*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_eq(struct hinic_eq *eq)
{
	struct msix_entry *entry = &eq->msix_entry;

	free_irq(entry->vector, eq);

	if (eq->type == HINIC_AEQ) {
		struct hinic_eq_work *aeq_work = &eq->aeq_work;

		cancel_work_sync(&aeq_work->work);
	} else if (eq->type == HINIC_CEQ) {
		tasklet_kill(&eq->ceq_tasklet);
	}

	free_eq_pages(eq);
}