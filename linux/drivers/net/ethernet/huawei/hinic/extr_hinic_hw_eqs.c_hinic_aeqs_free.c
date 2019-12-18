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
struct hinic_aeqs {int num_aeqs; int /*<<< orphan*/  workq; int /*<<< orphan*/ * aeq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_eq (int /*<<< orphan*/ *) ; 

void hinic_aeqs_free(struct hinic_aeqs *aeqs)
{
	int q_id;

	for (q_id = 0; q_id < aeqs->num_aeqs ; q_id++)
		remove_eq(&aeqs->aeq[q_id]);

	destroy_workqueue(aeqs->workq);
}