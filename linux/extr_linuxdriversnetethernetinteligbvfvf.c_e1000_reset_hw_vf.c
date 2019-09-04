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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int (* read_posted ) (struct e1000_hw*,int*,int) ;int /*<<< orphan*/  (* write_posted ) (struct e1000_hw*,int*,int) ;int /*<<< orphan*/  (* check_for_rst ) (struct e1000_hw*) ;} ;
struct e1000_mbx_info {TYPE_1__ ops; int /*<<< orphan*/  timeout; } ;
struct TYPE_4__ {int /*<<< orphan*/  perm_addr; } ;
struct e1000_hw {TYPE_2__ mac; struct e1000_mbx_info mbx; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_RST ; 
 int E1000_ERR_MAC_INIT ; 
 int E1000_VF_INIT_TIMEOUT ; 
 int /*<<< orphan*/  E1000_VF_MBX_INIT_TIMEOUT ; 
 int E1000_VF_RESET ; 
 int E1000_VT_MSGTYPE_ACK ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int*,int) ; 
 int stub3 (struct e1000_hw*,int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_reset_hw_vf(struct e1000_hw *hw)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	u32 timeout = E1000_VF_INIT_TIMEOUT;
	u32 ret_val = -E1000_ERR_MAC_INIT;
	u32 msgbuf[3];
	u8 *addr = (u8 *)(&msgbuf[1]);
	u32 ctrl;

	/* assert VF queue/interrupt reset */
	ctrl = er32(CTRL);
	ew32(CTRL, ctrl | E1000_CTRL_RST);

	/* we cannot initialize while the RSTI / RSTD bits are asserted */
	while (!mbx->ops.check_for_rst(hw) && timeout) {
		timeout--;
		udelay(5);
	}

	if (timeout) {
		/* mailbox timeout can now become active */
		mbx->timeout = E1000_VF_MBX_INIT_TIMEOUT;

		/* notify PF of VF reset completion */
		msgbuf[0] = E1000_VF_RESET;
		mbx->ops.write_posted(hw, msgbuf, 1);

		mdelay(10);

		/* set our "perm_addr" based on info provided by PF */
		ret_val = mbx->ops.read_posted(hw, msgbuf, 3);
		if (!ret_val) {
			if (msgbuf[0] == (E1000_VF_RESET |
					  E1000_VT_MSGTYPE_ACK))
				memcpy(hw->mac.perm_addr, addr, ETH_ALEN);
			else
				ret_val = -E1000_ERR_MAC_INIT;
		}
	}

	return ret_val;
}