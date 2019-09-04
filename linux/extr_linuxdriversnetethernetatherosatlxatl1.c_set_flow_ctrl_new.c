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
struct atl1_hw {scalar_t__ hw_addr; } ;

/* Variables and functions */
 scalar_t__ REG_RXQ_RRD_PAUSE_THRESH ; 
 scalar_t__ REG_RXQ_RXF_PAUSE_THRESH ; 
 scalar_t__ REG_SRAM_RRD_LEN ; 
 scalar_t__ REG_SRAM_RXF_LEN ; 
 int RXQ_RRD_PAUSE_TH_HI_MASK ; 
 int RXQ_RRD_PAUSE_TH_HI_SHIFT ; 
 int RXQ_RRD_PAUSE_TH_LO_MASK ; 
 int RXQ_RRD_PAUSE_TH_LO_SHIFT ; 
 int RXQ_RXF_PAUSE_TH_HI_MASK ; 
 int RXQ_RXF_PAUSE_TH_HI_SHIFT ; 
 int RXQ_RXF_PAUSE_TH_LO_MASK ; 
 int RXQ_RXF_PAUSE_TH_LO_SHIFT ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static void set_flow_ctrl_new(struct atl1_hw *hw)
{
	u32 hi, lo, value;

	/* RXF Flow Control */
	value = ioread32(hw->hw_addr + REG_SRAM_RXF_LEN);
	lo = value / 16;
	if (lo < 192)
		lo = 192;
	hi = value * 7 / 8;
	if (hi < lo)
		hi = lo + 16;
	value = ((hi & RXQ_RXF_PAUSE_TH_HI_MASK) << RXQ_RXF_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RXF_PAUSE_TH_LO_MASK) << RXQ_RXF_PAUSE_TH_LO_SHIFT);
	iowrite32(value, hw->hw_addr + REG_RXQ_RXF_PAUSE_THRESH);

	/* RRD Flow Control */
	value = ioread32(hw->hw_addr + REG_SRAM_RRD_LEN);
	lo = value / 8;
	hi = value * 7 / 8;
	if (lo < 2)
		lo = 2;
	if (hi < lo)
		hi = lo + 3;
	value = ((hi & RXQ_RRD_PAUSE_TH_HI_MASK) << RXQ_RRD_PAUSE_TH_HI_SHIFT) |
		((lo & RXQ_RRD_PAUSE_TH_LO_MASK) << RXQ_RRD_PAUSE_TH_LO_SHIFT);
	iowrite32(value, hw->hw_addr + REG_RXQ_RRD_PAUSE_THRESH);
}