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
struct vio_dev {int /*<<< orphan*/  unit_address; } ;
struct crq_queue {int /*<<< orphan*/  msg_token; scalar_t__ cur; int /*<<< orphan*/  msgs; } ;
struct crq_server_adapter {int /*<<< orphan*/  dev; struct crq_queue queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_REG_CRQ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  h_free_crq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvmc_reset_crq_queue(struct crq_server_adapter *adapter)
{
	struct vio_dev *vdev = to_vio_dev(adapter->dev);
	struct crq_queue *queue = &adapter->queue;
	int rc = 0;

	/* Close the CRQ */
	h_free_crq(vdev->unit_address);

	/* Clean out the queue */
	memset(queue->msgs, 0x00, PAGE_SIZE);
	queue->cur = 0;

	/* And re-open it again */
	rc = plpar_hcall_norets(H_REG_CRQ,
				vdev->unit_address,
				queue->msg_token, PAGE_SIZE);
	if (rc == 2)
		/* Adapter is good, but other end is not ready */
		dev_warn(adapter->dev, "Partner adapter not ready\n");
	else if (rc != 0)
		dev_err(adapter->dev, "couldn't register crq--rc 0x%x\n", rc);

	return rc;
}