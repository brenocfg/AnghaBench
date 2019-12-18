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
typedef  int u32 ;
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_PCIE_REMAP_2 ; 
 int MT_MCU_PCIE_REMAP_2_BASE ; 
 int MT_MCU_PCIE_REMAP_2_OFFSET ; 
 int MT_PCIE_REMAP_BASE_2 ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 

u32 mt7615_reg_map(struct mt7615_dev *dev, u32 addr)
{
	u32 base = addr & MT_MCU_PCIE_REMAP_2_BASE;
	u32 offset = addr & MT_MCU_PCIE_REMAP_2_OFFSET;

	mt76_wr(dev, MT_MCU_PCIE_REMAP_2, base);

	return MT_PCIE_REMAP_BASE_2 + offset;
}