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
typedef  int /*<<< orphan*/  u32 ;
struct atl2_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_WRITE_REG (struct atl2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL2_WRITE_REG_ARRAY (struct atl2_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RX_HASH_TABLE ; 
 int /*<<< orphan*/  atl2_init_flash_opcode (struct atl2_hw*) ; 
 int /*<<< orphan*/  atl2_init_pcie (struct atl2_hw*) ; 
 int /*<<< orphan*/  atl2_phy_init (struct atl2_hw*) ; 

__attribute__((used)) static s32 atl2_init_hw(struct atl2_hw *hw)
{
	u32 ret_val = 0;

	atl2_init_pcie(hw);

	/* Zero out the Multicast HASH table */
	/* clear the old settings from the multicast hash table */
	ATL2_WRITE_REG(hw, REG_RX_HASH_TABLE, 0);
	ATL2_WRITE_REG_ARRAY(hw, REG_RX_HASH_TABLE, 1, 0);

	atl2_init_flash_opcode(hw);

	ret_val = atl2_phy_init(hw);

	return ret_val;
}