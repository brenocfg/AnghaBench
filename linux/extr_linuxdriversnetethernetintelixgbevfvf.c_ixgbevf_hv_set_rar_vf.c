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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  perm_addr; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbevf_hv_set_rar_vf(struct ixgbe_hw *hw, u32 index, u8 *addr,
				 u32 vmdq)
{
	if (ether_addr_equal(addr, hw->mac.perm_addr))
		return 0;

	return -EOPNOTSUPP;
}