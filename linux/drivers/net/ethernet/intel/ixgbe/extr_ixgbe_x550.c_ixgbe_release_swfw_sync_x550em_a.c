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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int IXGBE_GSSR_TOKEN_SM ; 
 int /*<<< orphan*/  ixgbe_put_phy_token (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_release_swfw_sync_X540 (struct ixgbe_hw*,int) ; 

__attribute__((used)) static void ixgbe_release_swfw_sync_x550em_a(struct ixgbe_hw *hw, u32 mask)
{
	u32 hmask = mask & ~IXGBE_GSSR_TOKEN_SM;

	if (mask & IXGBE_GSSR_TOKEN_SM)
		ixgbe_put_phy_token(hw);

	if (hmask)
		ixgbe_release_swfw_sync_X540(hw, hmask);
}