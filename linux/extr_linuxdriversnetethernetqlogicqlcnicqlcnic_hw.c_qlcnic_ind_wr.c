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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_base0; } ;

/* Variables and functions */
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_wrt_reg_indirect (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_write_window_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qlcnic_ind_wr(struct qlcnic_adapter *adapter, u32 addr, u32 data)
{
	int ret = 0;

	if (qlcnic_82xx_check(adapter))
		qlcnic_write_window_reg(addr, adapter->ahw->pci_base0, data);
	else
		ret = qlcnic_83xx_wrt_reg_indirect(adapter, addr, data);

	return ret;
}