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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 scalar_t__ IXGBE_ERR_INVALID_ARGUMENT ; 
 int IXGBE_VF_SET_VLAN ; 
 int IXGBE_VT_MSGINFO_SHIFT ; 
 int IXGBE_VT_MSGTYPE_ACK ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 scalar_t__ ixgbevf_write_msg_read_ack (struct ixgbe_hw*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbevf_set_vfta_vf(struct ixgbe_hw *hw, u32 vlan, u32 vind,
			       bool vlan_on)
{
	u32 msgbuf[2];
	s32 err;

	msgbuf[0] = IXGBE_VF_SET_VLAN;
	msgbuf[1] = vlan;
	/* Setting the 8 bit field MSG INFO to TRUE indicates "add" */
	msgbuf[0] |= vlan_on << IXGBE_VT_MSGINFO_SHIFT;

	err = ixgbevf_write_msg_read_ack(hw, msgbuf, msgbuf,
					 ARRAY_SIZE(msgbuf));
	if (err)
		goto mbx_err;

	/* remove extra bits from the message */
	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;
	msgbuf[0] &= ~(0xFF << IXGBE_VT_MSGINFO_SHIFT);

	if (msgbuf[0] != (IXGBE_VF_SET_VLAN | IXGBE_VT_MSGTYPE_ACK))
		err = IXGBE_ERR_INVALID_ARGUMENT;

mbx_err:
	return err;
}