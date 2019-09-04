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
typedef  size_t u32 ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {TYPE_1__* vf_data; struct e1000_hw hw; } ;
struct TYPE_2__ {unsigned char* vf_mac_addresses; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 size_t BIT (size_t) ; 
 int /*<<< orphan*/  E1000_VFRE ; 
 int /*<<< orphan*/  E1000_VFTE ; 
 size_t E1000_VF_RESET ; 
 size_t E1000_VT_MSGTYPE_ACK ; 
 size_t E1000_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IGB_VF_FLAG_CTS ; 
 int /*<<< orphan*/  igb_set_vf_mac (struct igb_adapter*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  igb_vf_reset (struct igb_adapter*,size_t) ; 
 int /*<<< orphan*/  igb_write_mbx (struct e1000_hw*,size_t*,int,size_t) ; 
 int /*<<< orphan*/  is_zero_ether_addr (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 size_t rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void igb_vf_reset_msg(struct igb_adapter *adapter, u32 vf)
{
	struct e1000_hw *hw = &adapter->hw;
	unsigned char *vf_mac = adapter->vf_data[vf].vf_mac_addresses;
	u32 reg, msgbuf[3];
	u8 *addr = (u8 *)(&msgbuf[1]);

	/* process all the same items cleared in a function level reset */
	igb_vf_reset(adapter, vf);

	/* set vf mac address */
	igb_set_vf_mac(adapter, vf, vf_mac);

	/* enable transmit and receive for vf */
	reg = rd32(E1000_VFTE);
	wr32(E1000_VFTE, reg | BIT(vf));
	reg = rd32(E1000_VFRE);
	wr32(E1000_VFRE, reg | BIT(vf));

	adapter->vf_data[vf].flags |= IGB_VF_FLAG_CTS;

	/* reply to reset with ack and vf mac address */
	if (!is_zero_ether_addr(vf_mac)) {
		msgbuf[0] = E1000_VF_RESET | E1000_VT_MSGTYPE_ACK;
		memcpy(addr, vf_mac, ETH_ALEN);
	} else {
		msgbuf[0] = E1000_VF_RESET | E1000_VT_MSGTYPE_NACK;
	}
	igb_write_mbx(hw, msgbuf, 3, vf);
}