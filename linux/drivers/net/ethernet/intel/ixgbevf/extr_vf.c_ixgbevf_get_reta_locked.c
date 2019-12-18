#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int (* write_posted ) (struct ixgbe_hw*,int*,int) ;int (* read_posted ) (struct ixgbe_hw*,int*,int) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int api_version; TYPE_3__ mbx; TYPE_1__ mac; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int IXGBEVF_82599_RETA_SIZE ; 
 int IXGBE_ERR_MBX ; 
 int IXGBE_VFMAILBOX_SIZE ; 
 int IXGBE_VF_GET_RETA ; 
 int IXGBE_VT_MSGTYPE_ACK ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  ixgbe_mac_X550_vf ; 
#define  ixgbe_mbox_api_12 130 
#define  ixgbe_mbox_api_13 129 
#define  ixgbe_mbox_api_14 128 
 int stub1 (struct ixgbe_hw*,int*,int) ; 
 int stub2 (struct ixgbe_hw*,int*,int) ; 

int ixgbevf_get_reta_locked(struct ixgbe_hw *hw, u32 *reta, int num_rx_queues)
{
	int err, i, j;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];
	u32 *hw_reta = &msgbuf[1];
	u32 mask = 0;

	/* We have to use a mailbox for 82599 and x540 devices only.
	 * For these devices RETA has 128 entries.
	 * Also these VFs support up to 4 RSS queues. Therefore PF will compress
	 * 16 RETA entries in each DWORD giving 2 bits to each entry.
	 */
	int dwords = IXGBEVF_82599_RETA_SIZE / 16;

	/* We support the RSS querying for 82599 and x540 devices only.
	 * Thus return an error if API doesn't support RETA querying or querying
	 * is not supported for this device type.
	 */
	switch (hw->api_version) {
	case ixgbe_mbox_api_14:
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_12:
		if (hw->mac.type < ixgbe_mac_X550_vf)
			break;
		/* fall through */
	default:
		return -EOPNOTSUPP;
	}

	msgbuf[0] = IXGBE_VF_GET_RETA;

	err = hw->mbx.ops.write_posted(hw, msgbuf, 1);

	if (err)
		return err;

	err = hw->mbx.ops.read_posted(hw, msgbuf, dwords + 1);

	if (err)
		return err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the operation has been refused by a PF return -EPERM */
	if (msgbuf[0] == (IXGBE_VF_GET_RETA | IXGBE_VT_MSGTYPE_NACK))
		return -EPERM;

	/* If we didn't get an ACK there must have been
	 * some sort of mailbox error so we should treat it
	 * as such.
	 */
	if (msgbuf[0] != (IXGBE_VF_GET_RETA | IXGBE_VT_MSGTYPE_ACK))
		return IXGBE_ERR_MBX;

	/* ixgbevf doesn't support more than 2 queues at the moment */
	if (num_rx_queues > 1)
		mask = 0x1;

	for (i = 0; i < dwords; i++)
		for (j = 0; j < 16; j++)
			reta[i * 16 + j] = (hw_reta[i] >> (2 * j)) & mask;

	return 0;
}