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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ (* read_posted ) (struct e1000_hw*,int*,int) ;scalar_t__ (* write_posted ) (struct e1000_hw*,int*,int) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  msgbuf ;

/* Variables and functions */
 int E1000_VF_SET_MAC_ADDR ; 
 int E1000_VT_MSGTYPE_CTS ; 
 int E1000_VT_MSGTYPE_NACK ; 
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct e1000_hw*,int*,int) ; 
 scalar_t__ stub2 (struct e1000_hw*,int*,int) ; 

__attribute__((used)) static s32 e1000_set_uc_addr_vf(struct e1000_hw *hw, u32 sub_cmd, u8 *addr)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[3], msgbuf_chk;
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	memset(msgbuf, 0, sizeof(msgbuf));
	msgbuf[0] |= sub_cmd;
	msgbuf[0] |= E1000_VF_SET_MAC_ADDR;
	msgbuf_chk = msgbuf[0];

	if (addr)
		memcpy(msg_addr, addr, ETH_ALEN);

	ret_val = mbx->ops.write_posted(hw, msgbuf, 3);

	if (!ret_val)
		ret_val = mbx->ops.read_posted(hw, msgbuf, 3);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	if (!ret_val) {
		msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

		if (msgbuf[0] == (msgbuf_chk | E1000_VT_MSGTYPE_NACK))
			return -ENOSPC;
	}

	return ret_val;
}