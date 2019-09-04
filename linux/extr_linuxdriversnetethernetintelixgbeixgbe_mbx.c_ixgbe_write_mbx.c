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
typedef  scalar_t__ u16 ;
struct ixgbe_mbx_info {scalar_t__ size; TYPE_1__* ops; } ;
struct ixgbe_hw {struct ixgbe_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct ixgbe_hw*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

s32 ixgbe_write_mbx(struct ixgbe_hw *hw, u32 *msg, u16 size, u16 mbx_id)
{
	struct ixgbe_mbx_info *mbx = &hw->mbx;

	if (size > mbx->size)
		return IXGBE_ERR_MBX;

	if (!mbx->ops)
		return IXGBE_ERR_MBX;

	return mbx->ops->write(hw, msg, size, mbx_id);
}