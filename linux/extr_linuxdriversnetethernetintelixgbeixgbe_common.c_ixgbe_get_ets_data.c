#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ (* read ) (struct ixgbe_hw*,int,int*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_ETS_CFG ; 
 int IXGBE_ETS_TYPE_EMC_SHIFTED ; 
 int IXGBE_ETS_TYPE_MASK ; 
 scalar_t__ IXGBE_NOT_IMPLEMENTED ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int,int*) ; 

__attribute__((used)) static s32 ixgbe_get_ets_data(struct ixgbe_hw *hw, u16 *ets_cfg,
			      u16 *ets_offset)
{
	s32 status;

	status = hw->eeprom.ops.read(hw, IXGBE_ETS_CFG, ets_offset);
	if (status)
		return status;

	if ((*ets_offset == 0x0000) || (*ets_offset == 0xFFFF))
		return IXGBE_NOT_IMPLEMENTED;

	status = hw->eeprom.ops.read(hw, *ets_offset, ets_cfg);
	if (status)
		return status;

	if ((*ets_cfg & IXGBE_ETS_TYPE_MASK) != IXGBE_ETS_TYPE_EMC_SHIFTED)
		return IXGBE_NOT_IMPLEMENTED;

	return 0;
}