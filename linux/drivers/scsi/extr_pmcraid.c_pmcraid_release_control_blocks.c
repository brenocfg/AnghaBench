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
struct pmcraid_instance {int /*<<< orphan*/ * control_pool; TYPE_1__** cmd_list; } ;
struct TYPE_2__ {scalar_t__ ioa_cb_bus_addr; int /*<<< orphan*/ * ioa_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
pmcraid_release_control_blocks(
	struct pmcraid_instance *pinstance,
	int max_index
)
{
	int i;

	if (pinstance->control_pool == NULL)
		return;

	for (i = 0; i < max_index; i++) {
		dma_pool_free(pinstance->control_pool,
			      pinstance->cmd_list[i]->ioa_cb,
			      pinstance->cmd_list[i]->ioa_cb_bus_addr);
		pinstance->cmd_list[i]->ioa_cb = NULL;
		pinstance->cmd_list[i]->ioa_cb_bus_addr = 0;
	}
	dma_pool_destroy(pinstance->control_pool);
	pinstance->control_pool = NULL;
}