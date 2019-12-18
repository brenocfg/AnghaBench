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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_4__ {int (* write_posted ) (struct ixgbe_hw*,int*,int) ;int (* read_posted ) (struct ixgbe_hw*,int*,int) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int api_version; TYPE_2__ mbx; TYPE_3__ mac; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  IXGBEVF_RSS_HASH_KEY_SIZE ; 
 int IXGBE_ERR_MBX ; 
 int IXGBE_VFMAILBOX_SIZE ; 
 int IXGBE_VF_GET_RSS_KEY ; 
 int IXGBE_VT_MSGTYPE_ACK ; 
 int IXGBE_VT_MSGTYPE_CTS ; 
 int IXGBE_VT_MSGTYPE_NACK ; 
 int /*<<< orphan*/  ixgbe_mac_X550_vf ; 
#define  ixgbe_mbox_api_12 130 
#define  ixgbe_mbox_api_13 129 
#define  ixgbe_mbox_api_14 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ixgbe_hw*,int*,int) ; 
 int stub2 (struct ixgbe_hw*,int*,int) ; 

int ixgbevf_get_rss_key_locked(struct ixgbe_hw *hw, u8 *rss_key)
{
	int err;
	u32 msgbuf[IXGBE_VFMAILBOX_SIZE];

	/* We currently support the RSS Random Key retrieval for 82599 and x540
	 * devices only.
	 *
	 * Thus return an error if API doesn't support RSS Random Key retrieval
	 * or if the operation is not supported for this device type.
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

	msgbuf[0] = IXGBE_VF_GET_RSS_KEY;
	err = hw->mbx.ops.write_posted(hw, msgbuf, 1);

	if (err)
		return err;

	err = hw->mbx.ops.read_posted(hw, msgbuf, 11);

	if (err)
		return err;

	msgbuf[0] &= ~IXGBE_VT_MSGTYPE_CTS;

	/* If the operation has been refused by a PF return -EPERM */
	if (msgbuf[0] == (IXGBE_VF_GET_RSS_KEY | IXGBE_VT_MSGTYPE_NACK))
		return -EPERM;

	/* If we didn't get an ACK there must have been
	 * some sort of mailbox error so we should treat it
	 * as such.
	 */
	if (msgbuf[0] != (IXGBE_VF_GET_RSS_KEY | IXGBE_VT_MSGTYPE_ACK))
		return IXGBE_ERR_MBX;

	memcpy(rss_key, msgbuf + 1, IXGBEVF_RSS_HASH_KEY_SIZE);

	return 0;
}