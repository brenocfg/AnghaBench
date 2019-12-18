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
struct vio_dev {int irq; int /*<<< orphan*/  unit_address; } ;
struct ibmvmc_crq_msg {int dummy; } ;
struct crq_queue {int size; struct ibmvmc_crq_msg* msgs; int /*<<< orphan*/  msg_token; int /*<<< orphan*/  lock; scalar_t__ cur; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  work_task; struct crq_queue queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  H_REG_CRQ ; 
 int H_RESOURCE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,struct ibmvmc_crq_msg*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h_free_crq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmvmc_handle_event ; 
 int ibmvmc_reset_crq_queue (struct crq_server_adapter*) ; 
 int /*<<< orphan*/  ibmvmc_task ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static int ibmvmc_init_crq_queue(struct crq_server_adapter *adapter)
{
	struct vio_dev *vdev = to_vio_dev(adapter->dev);
	struct crq_queue *queue = &adapter->queue;
	int rc = 0;
	int retrc = 0;

	queue->msgs = (struct ibmvmc_crq_msg *)get_zeroed_page(GFP_KERNEL);

	if (!queue->msgs)
		goto malloc_failed;

	queue->size = PAGE_SIZE / sizeof(*queue->msgs);

	queue->msg_token = dma_map_single(adapter->dev, queue->msgs,
					  queue->size * sizeof(*queue->msgs),
					  DMA_BIDIRECTIONAL);

	if (dma_mapping_error(adapter->dev, queue->msg_token))
		goto map_failed;

	retrc = plpar_hcall_norets(H_REG_CRQ,
				   vdev->unit_address,
				   queue->msg_token, PAGE_SIZE);
	rc = retrc;

	if (rc == H_RESOURCE)
		rc = ibmvmc_reset_crq_queue(adapter);

	if (rc == 2) {
		dev_warn(adapter->dev, "Partner adapter not ready\n");
		retrc = 0;
	} else if (rc != 0) {
		dev_err(adapter->dev, "Error %d opening adapter\n", rc);
		goto reg_crq_failed;
	}

	queue->cur = 0;
	spin_lock_init(&queue->lock);

	tasklet_init(&adapter->work_task, ibmvmc_task, (unsigned long)adapter);

	if (request_irq(vdev->irq,
			ibmvmc_handle_event,
			0, "ibmvmc", (void *)adapter) != 0) {
		dev_err(adapter->dev, "couldn't register irq 0x%x\n",
			vdev->irq);
		goto req_irq_failed;
	}

	rc = vio_enable_interrupts(vdev);
	if (rc != 0) {
		dev_err(adapter->dev, "Error %d enabling interrupts!!!\n", rc);
		goto req_irq_failed;
	}

	return retrc;

req_irq_failed:
	/* Cannot have any work since we either never got our IRQ registered,
	 * or never got interrupts enabled
	 */
	tasklet_kill(&adapter->work_task);
	h_free_crq(vdev->unit_address);
reg_crq_failed:
	dma_unmap_single(adapter->dev,
			 queue->msg_token,
			 queue->size * sizeof(*queue->msgs), DMA_BIDIRECTIONAL);
map_failed:
	free_page((unsigned long)queue->msgs);
malloc_failed:
	return -ENOMEM;
}