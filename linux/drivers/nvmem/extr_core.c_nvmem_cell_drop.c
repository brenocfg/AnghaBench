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
struct nvmem_cell {struct nvmem_cell* name; int /*<<< orphan*/  np; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMEM_CELL_REMOVE ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvmem_cell*) ; 
 int /*<<< orphan*/  kfree (struct nvmem_cell*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_mutex ; 
 int /*<<< orphan*/  nvmem_notifier ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmem_cell_drop(struct nvmem_cell *cell)
{
	blocking_notifier_call_chain(&nvmem_notifier, NVMEM_CELL_REMOVE, cell);
	mutex_lock(&nvmem_mutex);
	list_del(&cell->node);
	mutex_unlock(&nvmem_mutex);
	of_node_put(cell->np);
	kfree(cell->name);
	kfree(cell);
}