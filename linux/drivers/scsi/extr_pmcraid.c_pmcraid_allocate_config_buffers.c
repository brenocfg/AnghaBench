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
struct pmcraid_resource_entry {int dummy; } ;
struct pmcraid_instance {int /*<<< orphan*/ * cfg_table; int /*<<< orphan*/  cfg_table_bus_addr; TYPE_1__* pdev; int /*<<< orphan*/  free_res_q; TYPE_2__* res_entries; } ;
struct pmcraid_config_table {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PMCRAID_MAX_RESOURCES ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pmcraid_allocate_hcams (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_err (char*) ; 
 int /*<<< orphan*/  pmcraid_release_config_buffers (struct pmcraid_instance*) ; 

__attribute__((used)) static int pmcraid_allocate_config_buffers(struct pmcraid_instance *pinstance)
{
	int i;

	pinstance->res_entries =
			kcalloc(PMCRAID_MAX_RESOURCES,
				sizeof(struct pmcraid_resource_entry),
				GFP_KERNEL);

	if (NULL == pinstance->res_entries) {
		pmcraid_err("failed to allocate memory for resource table\n");
		return -ENOMEM;
	}

	for (i = 0; i < PMCRAID_MAX_RESOURCES; i++)
		list_add_tail(&pinstance->res_entries[i].queue,
			      &pinstance->free_res_q);

	pinstance->cfg_table = dma_alloc_coherent(&pinstance->pdev->dev,
				     sizeof(struct pmcraid_config_table),
				     &pinstance->cfg_table_bus_addr,
				     GFP_KERNEL);

	if (NULL == pinstance->cfg_table) {
		pmcraid_err("couldn't alloc DMA memory for config table\n");
		pmcraid_release_config_buffers(pinstance);
		return -ENOMEM;
	}

	if (pmcraid_allocate_hcams(pinstance)) {
		pmcraid_err("could not alloc DMA memory for HCAMS\n");
		pmcraid_release_config_buffers(pinstance);
		return -ENOMEM;
	}

	return 0;
}