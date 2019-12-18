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
typedef  int /*<<< orphan*/  u64 ;
struct ibmveth_adapter {TYPE_1__* vdev; int /*<<< orphan*/  filter_list_dma; int /*<<< orphan*/  buffer_list_dma; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int H_BUSY ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int H_SUCCESS ; 
 int h_free_logical_lan (int /*<<< orphan*/ ) ; 
 int h_register_logical_lan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmveth_register_logical_lan(struct ibmveth_adapter *adapter,
        union ibmveth_buf_desc rxq_desc, u64 mac_address)
{
	int rc, try_again = 1;

	/*
	 * After a kexec the adapter will still be open, so our attempt to
	 * open it will fail. So if we get a failure we free the adapter and
	 * try again, but only once.
	 */
retry:
	rc = h_register_logical_lan(adapter->vdev->unit_address,
				    adapter->buffer_list_dma, rxq_desc.desc,
				    adapter->filter_list_dma, mac_address);

	if (rc != H_SUCCESS && try_again) {
		do {
			rc = h_free_logical_lan(adapter->vdev->unit_address);
		} while (H_IS_LONG_BUSY(rc) || (rc == H_BUSY));

		try_again = 0;
		goto retry;
	}

	return rc;
}