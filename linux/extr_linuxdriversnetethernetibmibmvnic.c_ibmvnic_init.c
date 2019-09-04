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
struct ibmvnic_adapter {int from_passive_init; int init_done_rc; int /*<<< orphan*/  state; int /*<<< orphan*/  init_done; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNIC_OPEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ibmvnic_send_crq_init (struct ibmvnic_adapter*) ; 
 int init_sub_crq_irqs (struct ibmvnic_adapter*) ; 
 int init_sub_crqs (struct ibmvnic_adapter*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  release_crq_queue (struct ibmvnic_adapter*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ibmvnic_init(struct ibmvnic_adapter *adapter)
{
	struct device *dev = &adapter->vdev->dev;
	unsigned long timeout = msecs_to_jiffies(30000);
	int rc;

	adapter->from_passive_init = false;

	adapter->init_done_rc = 0;
	ibmvnic_send_crq_init(adapter);
	if (!wait_for_completion_timeout(&adapter->init_done, timeout)) {
		dev_err(dev, "Initialization sequence timed out\n");
		return -1;
	}

	if (adapter->init_done_rc) {
		release_crq_queue(adapter);
		return adapter->init_done_rc;
	}

	if (adapter->from_passive_init) {
		adapter->state = VNIC_OPEN;
		adapter->from_passive_init = false;
		return -1;
	}

	rc = init_sub_crqs(adapter);
	if (rc) {
		dev_err(dev, "Initialization of sub crqs failed\n");
		release_crq_queue(adapter);
		return rc;
	}

	rc = init_sub_crq_irqs(adapter);
	if (rc) {
		dev_err(dev, "Failed to initialize sub crq irqs\n");
		release_crq_queue(adapter);
	}

	return rc;
}