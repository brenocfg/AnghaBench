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
struct qlcnic_hardware_context {int* extra_capability; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; struct qlcnic_hardware_context* ahw; } ;

/* Variables and functions */
 int QLCNIC_FW_CAPABILITY_2_MULTI_TX ; 
 int /*<<< orphan*/  __QLCNIC_MULTI_TX_UNIQUE ; 
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_check_multi_tx_capability(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (qlcnic_82xx_check(adapter) &&
	    (ahw->extra_capability[0] & QLCNIC_FW_CAPABILITY_2_MULTI_TX)) {
		test_and_set_bit(__QLCNIC_MULTI_TX_UNIQUE, &adapter->state);
		return 0;
	} else {
		return 1;
	}
}