#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_3__ {scalar_t__ pci_base0; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DEF_INT_MASK ; 
 int /*<<< orphan*/  QLCNIC_MBX_INTR_ENBL ; 
 scalar_t__ QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCWRX (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void qlcnic_83xx_disable_mbx_intr(struct qlcnic_adapter *adapter)
{
	u32 mask;

	mask = QLCRDX(adapter->ahw, QLCNIC_DEF_INT_MASK);
	writel(1, adapter->ahw->pci_base0 + mask);
	QLCWRX(adapter->ahw, QLCNIC_MBX_INTR_ENBL, 0);
}