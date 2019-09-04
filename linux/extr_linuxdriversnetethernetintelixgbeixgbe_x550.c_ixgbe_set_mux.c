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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  lan_id; } ;
struct ixgbe_hw {TYPE_1__ bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ESDP ; 
 int /*<<< orphan*/  IXGBE_ESDP_SDP1 ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_FLUSH (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ixgbe_set_mux(struct ixgbe_hw *hw, u8 state)
{
	u32 esdp;

	if (!hw->bus.lan_id)
		return;
	esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
	if (state)
		esdp |= IXGBE_ESDP_SDP1;
	else
		esdp &= ~IXGBE_ESDP_SDP1;
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_FLUSH(hw);
}