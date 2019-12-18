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
struct qdio_irq {TYPE_1__** input_qs; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tiq_list ; 
 int /*<<< orphan*/  tiq_list_lock ; 

void tiqdio_add_input_queues(struct qdio_irq *irq_ptr)
{
	mutex_lock(&tiq_list_lock);
	list_add_rcu(&irq_ptr->input_qs[0]->entry, &tiq_list);
	mutex_unlock(&tiq_list_lock);
}