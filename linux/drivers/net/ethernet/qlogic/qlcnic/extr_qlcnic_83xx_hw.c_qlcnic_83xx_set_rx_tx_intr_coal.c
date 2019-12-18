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
struct qlcnic_adapter {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int qlcnic_83xx_set_rx_intr_coal (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_set_tx_intr_coal (struct qlcnic_adapter*) ; 

int qlcnic_83xx_set_rx_tx_intr_coal(struct qlcnic_adapter *adapter)
{
	int err = 0;

	err = qlcnic_83xx_set_rx_intr_coal(adapter);
	if (err)
		netdev_err(adapter->netdev,
			   "failed to set Rx coalescing parameters\n");

	err = qlcnic_83xx_set_tx_intr_coal(adapter);
	if (err)
		netdev_err(adapter->netdev,
			   "failed to set Tx coalescing parameters\n");

	return err;
}