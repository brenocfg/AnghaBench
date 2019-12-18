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
union ibmveth_buf_desc {int /*<<< orphan*/  desc; } ;
struct ibmveth_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  fw_large_send_support; TYPE_1__* vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 unsigned long H_BUSY ; 
 unsigned long H_DROPPED ; 
 unsigned long H_SUCCESS ; 
 unsigned long h_send_logical_lan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static int ibmveth_send(struct ibmveth_adapter *adapter,
			union ibmveth_buf_desc *descs, unsigned long mss)
{
	unsigned long correlator;
	unsigned int retry_count;
	unsigned long ret;

	/*
	 * The retry count sets a maximum for the number of broadcast and
	 * multicast destinations within the system.
	 */
	retry_count = 1024;
	correlator = 0;
	do {
		ret = h_send_logical_lan(adapter->vdev->unit_address,
					     descs[0].desc, descs[1].desc,
					     descs[2].desc, descs[3].desc,
					     descs[4].desc, descs[5].desc,
					     correlator, &correlator, mss,
					     adapter->fw_large_send_support);
	} while ((ret == H_BUSY) && (retry_count--));

	if (ret != H_SUCCESS && ret != H_DROPPED) {
		netdev_err(adapter->netdev, "tx: h_send_logical_lan failed "
			   "with rc=%ld\n", ret);
		return 1;
	}

	return 0;
}