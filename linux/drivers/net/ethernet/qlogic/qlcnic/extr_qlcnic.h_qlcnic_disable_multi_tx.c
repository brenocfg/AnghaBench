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
struct qlcnic_adapter {int /*<<< orphan*/  drv_tx_rings; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_SINGLE_RING ; 
 int /*<<< orphan*/  __QLCNIC_MULTI_TX_UNIQUE ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void qlcnic_disable_multi_tx(struct qlcnic_adapter *adapter)
{
	test_and_clear_bit(__QLCNIC_MULTI_TX_UNIQUE, &adapter->state);
	adapter->drv_tx_rings = QLCNIC_SINGLE_RING;
}