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
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  msgbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  IXGBE_ERR_MBX ; 
 int IXGBE_VF_SET_MAC_ADDR ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbevf_get_mac_addr_vf (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_write_msg_read_ack (struct ixgbe_hw*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbevf_set_rar_vf(struct ixgbe_hw *hw, u32 index, u8 *addr,
			      u32 vmdq)
{
	u32 msgbuf[3];
	u8 *msg_addr = (u8 *)(&msgbuf[1]);
	s32 ret_val;

	memset(msgbuf, 0, sizeof(msgbuf));
	msgbuf[0] = IXGBE_VF_SET_MAC_ADDR;
	ether_addr_copy(msg_addr, addr);

	ret_val = ixgbevf_write_msg_read_ack(hw, msgbuf, msgbuf,
					     ARRAY_SIZE(msgbuf));
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* if nacked the address was rejected, use "perm_addr" */
	if (!ret_val &&
	    (msgbuf[0] == (IXGBE_VF_SET_MAC_ADDR | IXGBE_VT_MSGTYPE_NACK))) {
		ixgbevf_get_mac_addr_vf(hw, hw->mac.addr);
		return IXGBE_ERR_MBX;
	}

	return ret_val;
}