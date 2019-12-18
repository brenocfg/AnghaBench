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
struct qdio_q {int /*<<< orphan*/  entry; } ;
struct qdio_irq {struct qdio_q** input_qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  tiq_list_lock ; 

void tiqdio_remove_input_queues(struct qdio_irq *irq_ptr)
{
	struct qdio_q *q;

	q = irq_ptr->input_qs[0];
	if (!q)
		return;

	mutex_lock(&tiq_list_lock);
	list_del_rcu(&q->entry);
	mutex_unlock(&tiq_list_lock);
	synchronize_rcu();
	INIT_LIST_HEAD(&q->entry);
}