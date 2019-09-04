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
struct atl1_hw {scalar_t__ hw_addr; scalar_t__* mac_addr; } ;

/* Variables and functions */
 scalar_t__ REG_MAC_STA_ADDR ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void atl1_set_mac_addr(struct atl1_hw *hw)
{
	u32 value;
	/*
	 * 00-0B-6A-F6-00-DC
	 * 0:  6AF600DC   1: 000B
	 * low dword
	 */
	value = (((u32) hw->mac_addr[2]) << 24) |
	    (((u32) hw->mac_addr[3]) << 16) |
	    (((u32) hw->mac_addr[4]) << 8) | (((u32) hw->mac_addr[5]));
	iowrite32(value, hw->hw_addr + REG_MAC_STA_ADDR);
	/* high dword */
	value = (((u32) hw->mac_addr[0]) << 8) | (((u32) hw->mac_addr[1]));
	iowrite32(value, (hw->hw_addr + REG_MAC_STA_ADDR) + (1 << 2));
}