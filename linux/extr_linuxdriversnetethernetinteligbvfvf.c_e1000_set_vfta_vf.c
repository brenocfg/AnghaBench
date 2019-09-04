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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_posted ) (struct e1000_hw*,int*,int) ;int /*<<< orphan*/  (* write_posted ) (struct e1000_hw*,int*,int) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_ERR_MAC_INIT ; 
 int E1000_VF_SET_VLAN ; 
 int /*<<< orphan*/  E1000_VT_MSGINFO_SHIFT ; 
 int E1000_VT_MSGTYPE_CTS ; 
 int E1000_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int*,int) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int*,int) ; 

__attribute__((used)) static s32 e1000_set_vfta_vf(struct e1000_hw *hw, u16 vid, bool set)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	u32 msgbuf[2];
	s32 err;

	msgbuf[0] = E1000_VF_SET_VLAN;
	msgbuf[1] = vid;
	/* Setting the 8 bit field MSG INFO to true indicates "add" */
	if (set)
		msgbuf[0] |= BIT(E1000_VT_MSGINFO_SHIFT);

	mbx->ops.write_posted(hw, msgbuf, 2);

	err = mbx->ops.read_posted(hw, msgbuf, 2);

	msgbuf[0] &= ~E1000_VT_MSGTYPE_CTS;

	/* if nacked the vlan was rejected */
	if (!err && (msgbuf[0] == (E1000_VF_SET_VLAN | E1000_VT_MSGTYPE_NACK)))
		err = -E1000_ERR_MAC_INIT;

	return err;
}