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
struct nvmem_cell {TYPE_1__* nvmem; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMEM_CELL_ADD ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nvmem_cell*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_mutex ; 
 int /*<<< orphan*/  nvmem_notifier ; 

__attribute__((used)) static void nvmem_cell_add(struct nvmem_cell *cell)
{
	mutex_lock(&nvmem_mutex);
	list_add_tail(&cell->node, &cell->nvmem->cells);
	mutex_unlock(&nvmem_mutex);
	blocking_notifier_call_chain(&nvmem_notifier, NVMEM_CELL_ADD, cell);
}