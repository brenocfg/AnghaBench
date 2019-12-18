#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmcraid_instance {scalar_t__ cfg_table_bus_addr; TYPE_2__* res_entries; int /*<<< orphan*/ * cfg_table; TYPE_1__* pdev; } ;
struct pmcraid_config_table {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PMCRAID_MAX_RESOURCES ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcraid_release_hcams (struct pmcraid_instance*) ; 

__attribute__((used)) static void pmcraid_release_config_buffers(struct pmcraid_instance *pinstance)
{
	if (pinstance->cfg_table != NULL &&
	    pinstance->cfg_table_bus_addr != 0) {
		dma_free_coherent(&pinstance->pdev->dev,
				    sizeof(struct pmcraid_config_table),
				    pinstance->cfg_table,
				    pinstance->cfg_table_bus_addr);
		pinstance->cfg_table = NULL;
		pinstance->cfg_table_bus_addr = 0;
	}

	if (pinstance->res_entries != NULL) {
		int i;

		for (i = 0; i < PMCRAID_MAX_RESOURCES; i++)
			list_del(&pinstance->res_entries[i].queue);
		kfree(pinstance->res_entries);
		pinstance->res_entries = NULL;
	}

	pmcraid_release_hcams(pinstance);
}