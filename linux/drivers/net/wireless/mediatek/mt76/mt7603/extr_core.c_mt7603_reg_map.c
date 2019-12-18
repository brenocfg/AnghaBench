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
typedef  int u32 ;
struct mt7603_dev {int /*<<< orphan*/  mt76; TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wr ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_PCIE_REMAP_2 ; 
 int MT_MCU_PCIE_REMAP_2_BASE ; 
 int MT_MCU_PCIE_REMAP_2_OFFSET ; 
 int MT_PCIE_REMAP_BASE_2 ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

u32 mt7603_reg_map(struct mt7603_dev *dev, u32 addr)
{
	u32 base = addr & MT_MCU_PCIE_REMAP_2_BASE;
	u32 offset = addr & MT_MCU_PCIE_REMAP_2_OFFSET;

	dev->bus_ops->wr(&dev->mt76, MT_MCU_PCIE_REMAP_2, base);

	return MT_PCIE_REMAP_BASE_2 + offset;
}