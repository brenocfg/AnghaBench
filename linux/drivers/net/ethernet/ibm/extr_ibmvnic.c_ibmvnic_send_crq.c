#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ first; } ;
union ibmvnic_crq {TYPE_3__ generic; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int /*<<< orphan*/  active; } ;
struct ibmvnic_adapter {int /*<<< orphan*/  resetting; TYPE_2__ crq; int /*<<< orphan*/  netdev; TYPE_1__* vdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned int unit_address; struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int H_CLOSED ; 
 int /*<<< orphan*/  H_SEND_CRQ ; 
 scalar_t__ IBMVNIC_CRQ_INIT_CMD ; 
 int /*<<< orphan*/  VNIC_RESET_FATAL ; 
 scalar_t__ cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  ibmvnic_reset (struct ibmvnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvnic_send_crq(struct ibmvnic_adapter *adapter,
			    union ibmvnic_crq *crq)
{
	unsigned int ua = adapter->vdev->unit_address;
	struct device *dev = &adapter->vdev->dev;
	u64 *u64_crq = (u64 *)crq;
	int rc;

	netdev_dbg(adapter->netdev, "Sending CRQ: %016lx %016lx\n",
		   (unsigned long int)cpu_to_be64(u64_crq[0]),
		   (unsigned long int)cpu_to_be64(u64_crq[1]));

	if (!adapter->crq.active &&
	    crq->generic.first != IBMVNIC_CRQ_INIT_CMD) {
		dev_warn(dev, "Invalid request detected while CRQ is inactive, possible device state change during reset\n");
		return -EINVAL;
	}

	/* Make sure the hypervisor sees the complete request */
	mb();

	rc = plpar_hcall_norets(H_SEND_CRQ, ua,
				cpu_to_be64(u64_crq[0]),
				cpu_to_be64(u64_crq[1]));

	if (rc) {
		if (rc == H_CLOSED) {
			dev_warn(dev, "CRQ Queue closed\n");
			if (test_bit(0, &adapter->resetting))
				ibmvnic_reset(adapter, VNIC_RESET_FATAL);
		}

		dev_warn(dev, "Send error (rc=%d)\n", rc);
	}

	return rc;
}