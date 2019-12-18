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
struct pmcraid_timestamp_data {int dummy; } ;
struct pmcraid_instance {int /*<<< orphan*/  free_cmd_pool; struct pmcraid_cmd** cmd_list; int /*<<< orphan*/ * timestamp_data; int /*<<< orphan*/  timestamp_data_baddr; TYPE_1__* pdev; int /*<<< orphan*/ * inq_data; int /*<<< orphan*/  inq_data_baddr; int /*<<< orphan*/  num_hrrq; } ;
struct pmcraid_inquiry_data {int dummy; } ;
struct pmcraid_cmd {int /*<<< orphan*/  free_list; struct pmcraid_instance* drv_inst; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PMCRAID_MAX_CMD ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pmcraid_allocate_cmd_blocks (struct pmcraid_instance*) ; 
 scalar_t__ pmcraid_allocate_config_buffers (struct pmcraid_instance*) ; 
 scalar_t__ pmcraid_allocate_control_blocks (struct pmcraid_instance*) ; 
 scalar_t__ pmcraid_allocate_host_rrqs (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_err (char*,...) ; 
 int /*<<< orphan*/  pmcraid_init_cmdblk (struct pmcraid_cmd*,int) ; 
 int /*<<< orphan*/  pmcraid_release_buffers (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_release_cmd_blocks (struct pmcraid_instance*,int) ; 
 int /*<<< orphan*/  pmcraid_release_config_buffers (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_release_host_rrqs (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmcraid_init_buffers(struct pmcraid_instance *pinstance)
{
	int i;

	if (pmcraid_allocate_host_rrqs(pinstance)) {
		pmcraid_err("couldn't allocate memory for %d host rrqs\n",
			     pinstance->num_hrrq);
		return -ENOMEM;
	}

	if (pmcraid_allocate_config_buffers(pinstance)) {
		pmcraid_err("couldn't allocate memory for config buffers\n");
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		return -ENOMEM;
	}

	if (pmcraid_allocate_cmd_blocks(pinstance)) {
		pmcraid_err("couldn't allocate memory for cmd blocks\n");
		pmcraid_release_config_buffers(pinstance);
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		return -ENOMEM;
	}

	if (pmcraid_allocate_control_blocks(pinstance)) {
		pmcraid_err("couldn't allocate memory control blocks\n");
		pmcraid_release_config_buffers(pinstance);
		pmcraid_release_cmd_blocks(pinstance, PMCRAID_MAX_CMD);
		pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);
		return -ENOMEM;
	}

	/* allocate DMAable memory for page D0 INQUIRY buffer */
	pinstance->inq_data = dma_alloc_coherent(&pinstance->pdev->dev,
					sizeof(struct pmcraid_inquiry_data),
					&pinstance->inq_data_baddr, GFP_KERNEL);
	if (pinstance->inq_data == NULL) {
		pmcraid_err("couldn't allocate DMA memory for INQUIRY\n");
		pmcraid_release_buffers(pinstance);
		return -ENOMEM;
	}

	/* allocate DMAable memory for set timestamp data buffer */
	pinstance->timestamp_data = dma_alloc_coherent(&pinstance->pdev->dev,
					sizeof(struct pmcraid_timestamp_data),
					&pinstance->timestamp_data_baddr,
					GFP_KERNEL);
	if (pinstance->timestamp_data == NULL) {
		pmcraid_err("couldn't allocate DMA memory for \
				set time_stamp \n");
		pmcraid_release_buffers(pinstance);
		return -ENOMEM;
	}


	/* Initialize all the command blocks and add them to free pool. No
	 * need to lock (free_pool_lock) as this is done in initialization
	 * itself
	 */
	for (i = 0; i < PMCRAID_MAX_CMD; i++) {
		struct pmcraid_cmd *cmdp = pinstance->cmd_list[i];
		pmcraid_init_cmdblk(cmdp, i);
		cmdp->drv_inst = pinstance;
		list_add_tail(&cmdp->free_list, &pinstance->free_cmd_pool);
	}

	return 0;
}