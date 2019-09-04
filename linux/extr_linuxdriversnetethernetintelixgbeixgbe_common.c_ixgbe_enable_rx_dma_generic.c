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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* disable_rx ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* enable_rx ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IXGBE_RXCTRL_RXEN ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*) ; 

s32 ixgbe_enable_rx_dma_generic(struct ixgbe_hw *hw, u32 regval)
{
	if (regval & IXGBE_RXCTRL_RXEN)
		hw->mac.ops.enable_rx(hw);
	else
		hw->mac.ops.disable_rx(hw);

	return 0;
}