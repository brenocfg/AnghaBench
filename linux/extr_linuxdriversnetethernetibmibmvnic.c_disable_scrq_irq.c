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
struct ibmvnic_sub_crq_queue {int /*<<< orphan*/  hw_irq; } ;
struct ibmvnic_adapter {TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_DISABLE_VIO_INTERRUPT ; 
 int /*<<< orphan*/  H_VIOCTL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_scrq_irq(struct ibmvnic_adapter *adapter,
			    struct ibmvnic_sub_crq_queue *scrq)
{
	struct device *dev = &adapter->vdev->dev;
	unsigned long rc;

	rc = plpar_hcall_norets(H_VIOCTL, adapter->vdev->unit_address,
				H_DISABLE_VIO_INTERRUPT, scrq->hw_irq, 0, 0);
	if (rc)
		dev_err(dev, "Couldn't disable scrq irq 0x%lx. rc=%ld\n",
			scrq->hw_irq, rc);
	return rc;
}