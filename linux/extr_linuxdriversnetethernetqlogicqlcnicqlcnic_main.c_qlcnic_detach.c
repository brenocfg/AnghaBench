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
struct qlcnic_adapter {scalar_t__ is_up; } ;

/* Variables and functions */
 scalar_t__ QLCNIC_ADAPTER_UP_MAGIC ; 
 int /*<<< orphan*/  qlcnic_free_hw_resources (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_irq (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_free_sw_resources (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_napi_del (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_release_rx_buffers (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_remove_sysfs_entries (struct qlcnic_adapter*) ; 

void qlcnic_detach(struct qlcnic_adapter *adapter)
{
	if (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		return;

	qlcnic_remove_sysfs_entries(adapter);

	qlcnic_free_hw_resources(adapter);
	qlcnic_release_rx_buffers(adapter);
	qlcnic_free_irq(adapter);
	qlcnic_napi_del(adapter);
	qlcnic_free_sw_resources(adapter);

	adapter->is_up = 0;
}