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
struct TYPE_2__ {scalar_t__ (* write ) (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; int /*<<< orphan*/  timeout; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ERR_MBX ; 
 scalar_t__ igb_poll_for_ack (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 igb_write_posted_mbx(struct e1000_hw *hw, u32 *msg, u16 size,
				u16 mbx_id)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	s32 ret_val = -E1000_ERR_MBX;

	/* exit if either we can't write or there isn't a defined timeout */
	if (!mbx->ops.write || !mbx->timeout)
		goto out;

	/* send msg */
	ret_val = mbx->ops.write(hw, msg, size, mbx_id);

	/* if msg sent wait until we receive an ack */
	if (!ret_val)
		ret_val = igb_poll_for_ack(hw, mbx_id);
out:
	return ret_val;
}