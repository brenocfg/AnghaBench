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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  perm_addr; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  FM10K_ERR_INVALID_MAC_ADDR ; 
 int /*<<< orphan*/  FM10K_SM_AREA (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__*) ; 
 int fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_read_mac_addr_pf(struct fm10k_hw *hw)
{
	u8 perm_addr[ETH_ALEN];
	u32 serial_num;

	serial_num = fm10k_read_reg(hw, FM10K_SM_AREA(1));

	/* last byte should be all 1's */
	if ((~serial_num) << 24)
		return  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[0] = (u8)(serial_num >> 24);
	perm_addr[1] = (u8)(serial_num >> 16);
	perm_addr[2] = (u8)(serial_num >> 8);

	serial_num = fm10k_read_reg(hw, FM10K_SM_AREA(0));

	/* first byte should be all 1's */
	if ((~serial_num) >> 24)
		return  FM10K_ERR_INVALID_MAC_ADDR;

	perm_addr[3] = (u8)(serial_num >> 16);
	perm_addr[4] = (u8)(serial_num >> 8);
	perm_addr[5] = (u8)(serial_num);

	ether_addr_copy(hw->mac.perm_addr, perm_addr);
	ether_addr_copy(hw->mac.addr, perm_addr);

	return 0;
}