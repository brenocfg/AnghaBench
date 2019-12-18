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
typedef  union scu_remote_node_context {int dummy; } scu_remote_node_context ;
typedef  int /*<<< orphan*/  u32 ;
struct scu_task_context {int dummy; } ;
struct isci_request {struct isci_host* isci_host; int /*<<< orphan*/  request_daddr; struct isci_host* owning_controller; int /*<<< orphan*/ * tc; } ;
struct isci_host {int remote_node_entries; int task_context_entries; struct isci_request** reqs; int /*<<< orphan*/ * task_context_table; void* ufi_buf; int /*<<< orphan*/  ufi_dma; int /*<<< orphan*/  tc_dma; void* remote_node_context_table; int /*<<< orphan*/  rnc_dma; void* completion_queue; int /*<<< orphan*/  cq_dma; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCI_MAX_IO_REQUESTS ; 
 size_t SCI_UFI_TOTAL_SIZE ; 
 int SCU_MAX_COMPLETION_QUEUE_ENTRIES ; 
 void* dmam_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sci_controller_dma_alloc(struct isci_host *ihost)
{
	struct device *dev = &ihost->pdev->dev;
	size_t size;
	int i;

	/* detect re-initialization */
	if (ihost->completion_queue)
		return 0;

	size = SCU_MAX_COMPLETION_QUEUE_ENTRIES * sizeof(u32);
	ihost->completion_queue = dmam_alloc_coherent(dev, size, &ihost->cq_dma,
						      GFP_KERNEL);
	if (!ihost->completion_queue)
		return -ENOMEM;

	size = ihost->remote_node_entries * sizeof(union scu_remote_node_context);
	ihost->remote_node_context_table = dmam_alloc_coherent(dev, size, &ihost->rnc_dma,
							       GFP_KERNEL);

	if (!ihost->remote_node_context_table)
		return -ENOMEM;

	size = ihost->task_context_entries * sizeof(struct scu_task_context),
	ihost->task_context_table = dmam_alloc_coherent(dev, size, &ihost->tc_dma,
							GFP_KERNEL);
	if (!ihost->task_context_table)
		return -ENOMEM;

	size = SCI_UFI_TOTAL_SIZE;
	ihost->ufi_buf = dmam_alloc_coherent(dev, size, &ihost->ufi_dma, GFP_KERNEL);
	if (!ihost->ufi_buf)
		return -ENOMEM;

	for (i = 0; i < SCI_MAX_IO_REQUESTS; i++) {
		struct isci_request *ireq;
		dma_addr_t dma;

		ireq = dmam_alloc_coherent(dev, sizeof(*ireq), &dma, GFP_KERNEL);
		if (!ireq)
			return -ENOMEM;

		ireq->tc = &ihost->task_context_table[i];
		ireq->owning_controller = ihost;
		ireq->request_daddr = dma;
		ireq->isci_host = ihost;
		ihost->reqs[i] = ireq;
	}

	return 0;
}