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
struct vio_device_id {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  unit_address; } ;
struct crq_server_adapter {int /*<<< orphan*/ * reset_task; int /*<<< orphan*/ * dev; int /*<<< orphan*/  reset_wait_queue; int /*<<< orphan*/  riobn; int /*<<< orphan*/  liobn; } ;
struct TYPE_2__ {void* state; } ;

/* Variables and functions */
 int EPERM ; 
 int H_RESOURCE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct crq_server_adapter*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__ ibmvmc ; 
 struct crq_server_adapter ibmvmc_adapter ; 
 int ibmvmc_init_crq_queue (struct crq_server_adapter*) ; 
 int /*<<< orphan*/  ibmvmc_reset_task ; 
 scalar_t__ ibmvmc_send_crq (struct crq_server_adapter*,int,int /*<<< orphan*/ ) ; 
 void* ibmvmc_state_crqinit ; 
 void* ibmvmc_state_failed ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct crq_server_adapter*,char*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct crq_server_adapter*,int /*<<< orphan*/ ,int) ; 
 int read_dma_window (struct vio_dev*,struct crq_server_adapter*) ; 

__attribute__((used)) static int ibmvmc_probe(struct vio_dev *vdev, const struct vio_device_id *id)
{
	struct crq_server_adapter *adapter = &ibmvmc_adapter;
	int rc;

	dev_set_drvdata(&vdev->dev, NULL);
	memset(adapter, 0, sizeof(*adapter));
	adapter->dev = &vdev->dev;

	dev_info(adapter->dev, "Probe for UA 0x%x\n", vdev->unit_address);

	rc = read_dma_window(vdev, adapter);
	if (rc != 0) {
		ibmvmc.state = ibmvmc_state_failed;
		return -1;
	}

	dev_dbg(adapter->dev, "Probe: liobn 0x%x, riobn 0x%x\n",
		adapter->liobn, adapter->riobn);

	init_waitqueue_head(&adapter->reset_wait_queue);
	adapter->reset_task = kthread_run(ibmvmc_reset_task, adapter, "ibmvmc");
	if (IS_ERR(adapter->reset_task)) {
		dev_err(adapter->dev, "Failed to start reset thread\n");
		ibmvmc.state = ibmvmc_state_failed;
		rc = PTR_ERR(adapter->reset_task);
		adapter->reset_task = NULL;
		return rc;
	}

	rc = ibmvmc_init_crq_queue(adapter);
	if (rc != 0 && rc != H_RESOURCE) {
		dev_err(adapter->dev, "Error initializing CRQ.  rc = 0x%x\n",
			rc);
		ibmvmc.state = ibmvmc_state_failed;
		goto crq_failed;
	}

	ibmvmc.state = ibmvmc_state_crqinit;

	/* Try to send an initialization message.  Note that this is allowed
	 * to fail if the other end is not acive.  In that case we just wait
	 * for the other side to initialize.
	 */
	if (ibmvmc_send_crq(adapter, 0xC001000000000000LL, 0) != 0 &&
	    rc != H_RESOURCE)
		dev_warn(adapter->dev, "Failed to send initialize CRQ message\n");

	dev_set_drvdata(&vdev->dev, adapter);

	return 0;

crq_failed:
	kthread_stop(adapter->reset_task);
	adapter->reset_task = NULL;
	return -EPERM;
}