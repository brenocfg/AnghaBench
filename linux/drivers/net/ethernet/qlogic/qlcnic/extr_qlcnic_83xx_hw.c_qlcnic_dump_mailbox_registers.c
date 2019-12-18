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
typedef  scalar_t__ u32 ;
struct qlcnic_hardware_context {scalar_t__ pci_base0; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DEF_INT_MASK ; 
 int /*<<< orphan*/  QLCNIC_FW_MBX_CTRL ; 
 int /*<<< orphan*/  QLCNIC_HOST_MBX_CTRL ; 
 int /*<<< orphan*/  QLCNIC_MBX_INTR_ENBL ; 
 scalar_t__ QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline void qlcnic_dump_mailbox_registers(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 offset;

	offset = QLCRDX(ahw, QLCNIC_DEF_INT_MASK);
	dev_info(&adapter->pdev->dev, "Mbx interrupt mask=0x%x, Mbx interrupt enable=0x%x, Host mbx control=0x%x, Fw mbx control=0x%x",
		 readl(ahw->pci_base0 + offset),
		 QLCRDX(ahw, QLCNIC_MBX_INTR_ENBL),
		 QLCRDX(ahw, QLCNIC_HOST_MBX_CTRL),
		 QLCRDX(ahw, QLCNIC_FW_MBX_CTRL));
}