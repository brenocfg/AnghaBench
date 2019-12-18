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
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_ROM_LOCK_ID ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_pcie_sem_lock (struct qlcnic_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_pcie_sem_unlock (struct qlcnic_adapter*,int) ; 

__attribute__((used)) static void qlcnic_rom_lock_recovery(struct qlcnic_adapter *adapter)
{
	if (qlcnic_pcie_sem_lock(adapter, 2, QLCNIC_ROM_LOCK_ID))
		dev_info(&adapter->pdev->dev, "Resetting rom_lock\n");

	qlcnic_pcie_sem_unlock(adapter, 2);
}