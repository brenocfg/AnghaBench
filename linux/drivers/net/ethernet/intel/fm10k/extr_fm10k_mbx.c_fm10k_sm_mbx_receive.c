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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_info {scalar_t__ mbmem_len; scalar_t__ head; scalar_t__ pushed; } ;
struct fm10k_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_mbx_dequeue_rx (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_head_sub (struct fm10k_mbx_info*,scalar_t__) ; 
 scalar_t__ fm10k_mbx_push_tail (struct fm10k_hw*,struct fm10k_mbx_info*,scalar_t__) ; 

__attribute__((used)) static s32 fm10k_sm_mbx_receive(struct fm10k_hw *hw,
				struct fm10k_mbx_info *mbx,
				u16 tail)
{
	/* reduce length by 1 to convert to a mask */
	u16 mbmem_len = mbx->mbmem_len - 1;
	s32 err;

	/* push tail in front of head */
	if (tail < mbx->head)
		tail += mbmem_len;

	/* copy data to the Rx FIFO */
	err = fm10k_mbx_push_tail(hw, mbx, tail);
	if (err < 0)
		return err;

	/* process messages if we have received any */
	fm10k_mbx_dequeue_rx(hw, mbx);

	/* guarantee head aligns with the end of the last message */
	mbx->head = fm10k_mbx_head_sub(mbx, mbx->pushed);
	mbx->pushed = 0;

	/* clear any extra bits left over since index adds 1 extra bit */
	if (mbx->head > mbmem_len)
		mbx->head -= mbmem_len;

	return err;
}