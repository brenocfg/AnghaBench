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
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int E1000_KMRNCTRLSTA_OFFSET ; 
 int E1000_KMRNCTRLSTA_OFFSET_SHIFT ; 
 int /*<<< orphan*/  KMRNCTRLSTA ; 
 scalar_t__ e1000_acquire_mac_csr_80003es2lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_release_mac_csr_80003es2lan (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_write_kmrn_reg_80003es2lan(struct e1000_hw *hw, u32 offset,
					    u16 data)
{
	u32 kmrnctrlsta;
	s32 ret_val;

	ret_val = e1000_acquire_mac_csr_80003es2lan(hw);
	if (ret_val)
		return ret_val;

	kmrnctrlsta = ((offset << E1000_KMRNCTRLSTA_OFFSET_SHIFT) &
		       E1000_KMRNCTRLSTA_OFFSET) | data;
	ew32(KMRNCTRLSTA, kmrnctrlsta);
	e1e_flush();

	udelay(2);

	e1000_release_mac_csr_80003es2lan(hw);

	return ret_val;
}