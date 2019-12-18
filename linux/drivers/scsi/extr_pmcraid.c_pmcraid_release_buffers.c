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
struct pmcraid_instance {scalar_t__ timestamp_data_baddr; int /*<<< orphan*/ * timestamp_data; TYPE_1__* pdev; scalar_t__ inq_data_baddr; int /*<<< orphan*/ * inq_data; int /*<<< orphan*/  num_hrrq; } ;
struct pmcraid_inquiry_data {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_MAX_CMD ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pmcraid_release_cmd_blocks (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_release_config_buffers (struct pmcraid_instance*) ; 
 int /*<<< orphan*/  pmcraid_release_control_blocks (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_release_host_rrqs (struct pmcraid_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_release_buffers(struct pmcraid_instance *pinstance)
{
	pmcraid_release_config_buffers(pinstance);
	pmcraid_release_control_blocks(pinstance, PMCRAID_MAX_CMD);
	pmcraid_release_cmd_blocks(pinstance, PMCRAID_MAX_CMD);
	pmcraid_release_host_rrqs(pinstance, pinstance->num_hrrq);

	if (pinstance->inq_data != NULL) {
		dma_free_coherent(&pinstance->pdev->dev,
				    sizeof(struct pmcraid_inquiry_data),
				    pinstance->inq_data,
				    pinstance->inq_data_baddr);

		pinstance->inq_data = NULL;
		pinstance->inq_data_baddr = 0;
	}

	if (pinstance->timestamp_data != NULL) {
		dma_free_coherent(&pinstance->pdev->dev,
				    sizeof(struct pmcraid_timestamp_data),
				    pinstance->timestamp_data,
				    pinstance->timestamp_data_baddr);

		pinstance->timestamp_data = NULL;
		pinstance->timestamp_data_baddr = 0;
	}
}