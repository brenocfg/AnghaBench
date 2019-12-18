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
struct irq_desc {int /*<<< orphan*/  irq_data; } ;
struct irq_chip {int /*<<< orphan*/  (* irq_eoi ) (int /*<<< orphan*/ *) ;} ;
struct ibmvnic_sub_crq_queue {int hw_irq; int /*<<< orphan*/  irq; } ;
struct ibmvnic_adapter {scalar_t__ reset_reason; TYPE_1__* vdev; int /*<<< orphan*/  resetting; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_ENABLE_VIO_INTERRUPT ; 
 int /*<<< orphan*/  H_VIOCTL ; 
 scalar_t__ VNIC_RESET_MOBILITY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 struct irq_chip* irq_desc_get_chip (struct irq_desc*) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 
 unsigned long plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enable_scrq_irq(struct ibmvnic_adapter *adapter,
			   struct ibmvnic_sub_crq_queue *scrq)
{
	struct device *dev = &adapter->vdev->dev;
	unsigned long rc;

	if (scrq->hw_irq > 0x100000000ULL) {
		dev_err(dev, "bad hw_irq = %lx\n", scrq->hw_irq);
		return 1;
	}

	if (test_bit(0, &adapter->resetting) &&
	    adapter->reset_reason == VNIC_RESET_MOBILITY) {
		struct irq_desc *desc = irq_to_desc(scrq->irq);
		struct irq_chip *chip = irq_desc_get_chip(desc);

		chip->irq_eoi(&desc->irq_data);
	}

	rc = plpar_hcall_norets(H_VIOCTL, adapter->vdev->unit_address,
				H_ENABLE_VIO_INTERRUPT, scrq->hw_irq, 0, 0);
	if (rc)
		dev_err(dev, "Couldn't enable scrq irq 0x%lx. rc=%ld\n",
			scrq->hw_irq, rc);
	return rc;
}