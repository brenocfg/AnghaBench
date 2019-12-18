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
struct pmcraid_instance {int num_hrrq; int* host_toggle_bit; int /*<<< orphan*/ * hrrq_lock; scalar_t__* hrrq_start; scalar_t__* hrrq_end; scalar_t__* hrrq_curr; int /*<<< orphan*/ * hrrq_start_bus_addr; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HRRQ_ENTRY_SIZE ; 
 int PMCRAID_MAX_CMD ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmcraid_err (char*,int) ; 
 int /*<<< orphan*/  pmcraid_release_host_rrqs (struct pmcraid_instance*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmcraid_allocate_host_rrqs(struct pmcraid_instance *pinstance)
{
	int i, buffer_size;

	buffer_size = HRRQ_ENTRY_SIZE * PMCRAID_MAX_CMD;

	for (i = 0; i < pinstance->num_hrrq; i++) {
		pinstance->hrrq_start[i] =
			dma_alloc_coherent(&pinstance->pdev->dev, buffer_size,
					   &pinstance->hrrq_start_bus_addr[i],
					   GFP_KERNEL);
		if (!pinstance->hrrq_start[i]) {
			pmcraid_err("pci_alloc failed for hrrq vector : %d\n",
				    i);
			pmcraid_release_host_rrqs(pinstance, i);
			return -ENOMEM;
		}

		memset(pinstance->hrrq_start[i], 0, buffer_size);
		pinstance->hrrq_curr[i] = pinstance->hrrq_start[i];
		pinstance->hrrq_end[i] =
			pinstance->hrrq_start[i] + PMCRAID_MAX_CMD - 1;
		pinstance->host_toggle_bit[i] = 1;
		spin_lock_init(&pinstance->hrrq_lock[i]);
	}
	return 0;
}