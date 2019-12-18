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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ixgbe_mbx_info {TYPE_1__* ops; int /*<<< orphan*/  timeout; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ (* write ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_MBX ; 
 scalar_t__ ixgbe_poll_for_ack (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_write_posted_mbx(struct ixgbe_hw *hw, u32 *msg, u16 size,
			   u16 mbx_id)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;
	s32 ret_val;

	/* exit if either we can't write or there isn't a defined timeout */
	if (!mbx->ops || !mbx->timeout)
		return IXGBE_ERR_MBX;

	/* send msg */
	ret_val = mbx->ops->write(hw, msg, size, mbx_id);
	if (ret_val)
		return ret_val;

	/* if msg sent wait until we receive an ack */
	return ixgbe_poll_for_ack(hw, mbx_id);
}