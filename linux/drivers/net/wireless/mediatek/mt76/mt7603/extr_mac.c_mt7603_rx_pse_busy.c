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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MT_CLIENT_BASE_PHYS_ADDR ; 
 scalar_t__ MT_CLIENT_STATUS ; 
 int MT_MCU_DEBUG_RESET ; 
 int MT_MCU_DEBUG_RESET_QUEUES ; 
 scalar_t__ is_mt7628 (struct mt7603_dev*) ; 
 int mt7603_reg_map (struct mt7603_dev*,scalar_t__) ; 
 scalar_t__ mt7603_rx_fifo_busy (struct mt7603_dev*) ; 
 int mt76_rr (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int,int) ; 

__attribute__((used)) static bool mt7603_rx_pse_busy(struct mt7603_dev *dev)
{
	u32 addr, val;

	if (mt76_rr(dev, MT_MCU_DEBUG_RESET) & MT_MCU_DEBUG_RESET_QUEUES)
		return true;

	if (mt7603_rx_fifo_busy(dev))
		return false;

	addr = mt7603_reg_map(dev, MT_CLIENT_BASE_PHYS_ADDR + MT_CLIENT_STATUS);
	mt76_wr(dev, addr, 3);
	val = mt76_rr(dev, addr) >> 16;

	if (is_mt7628(dev) && (val & 0x4001) == 0x4001)
		return true;

	return (val & 0x8001) == 0x8001 || (val & 0xe001) == 0xe001;
}