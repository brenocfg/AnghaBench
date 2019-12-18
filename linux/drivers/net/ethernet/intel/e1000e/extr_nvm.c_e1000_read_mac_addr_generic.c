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
typedef  void* u8 ;
typedef  size_t u32 ;
typedef  size_t u16 ;
struct TYPE_2__ {void** perm_addr; void** addr; } ;
struct e1000_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t E1000_RAH_MAC_ADDR_LEN ; 
 size_t E1000_RAL_MAC_ADDR_LEN ; 
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  RAH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL (int /*<<< orphan*/ ) ; 
 size_t er32 (int /*<<< orphan*/ ) ; 

s32 e1000_read_mac_addr_generic(struct e1000_hw *hw)
{
	u32 rar_high;
	u32 rar_low;
	u16 i;

	rar_high = er32(RAH(0));
	rar_low = er32(RAL(0));

	for (i = 0; i < E1000_RAL_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i] = (u8)(rar_low >> (i * 8));

	for (i = 0; i < E1000_RAH_MAC_ADDR_LEN; i++)
		hw->mac.perm_addr[i + 4] = (u8)(rar_high >> (i * 8));

	for (i = 0; i < ETH_ALEN; i++)
		hw->mac.addr[i] = hw->mac.perm_addr[i];

	return 0;
}