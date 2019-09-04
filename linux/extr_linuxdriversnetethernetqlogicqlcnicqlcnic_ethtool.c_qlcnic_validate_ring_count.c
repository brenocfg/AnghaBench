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
typedef  scalar_t__ u8 ;
struct qlcnic_adapter {scalar_t__ max_sds_rings; scalar_t__ max_tx_rings; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int qlcnic_validate_ring_count(struct qlcnic_adapter *adapter,
				      u8 rx_ring, u8 tx_ring)
{
	if (rx_ring == 0 || tx_ring == 0)
		return -EINVAL;

	if (rx_ring != 0) {
		if (rx_ring > adapter->max_sds_rings) {
			netdev_err(adapter->netdev,
				   "Invalid ring count, SDS ring count %d should not be greater than max %d driver sds rings.\n",
				   rx_ring, adapter->max_sds_rings);
			return -EINVAL;
		}
	}

	 if (tx_ring != 0) {
		if (tx_ring > adapter->max_tx_rings) {
			netdev_err(adapter->netdev,
				   "Invalid ring count, Tx ring count %d should not be greater than max %d driver Tx rings.\n",
				   tx_ring, adapter->max_tx_rings);
			return -EINVAL;
		}
	}

	return 0;
}