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
struct TYPE_2__ {scalar_t__ hw_addr; } ;
struct atl1_adapter {TYPE_1__ hw; } ;

/* Variables and functions */
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void atl1_pcie_patch(struct atl1_adapter *adapter)
{
	u32 value;

	/* much vendor magic here */
	value = 0x6500;
	iowrite32(value, adapter->hw.hw_addr + 0x12FC);
	/* pcie flow control mode change */
	value = ioread32(adapter->hw.hw_addr + 0x1008);
	value |= 0x8000;
	iowrite32(value, adapter->hw.hw_addr + 0x1008);
}