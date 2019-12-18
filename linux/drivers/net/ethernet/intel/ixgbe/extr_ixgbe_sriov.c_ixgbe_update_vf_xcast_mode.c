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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct ixgbe_adapter {TYPE_2__* vfinfo; struct ixgbe_hw hw; } ;
struct TYPE_4__ {int vf_api; int xcast_mode; int /*<<< orphan*/  trusted; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  IXGBEVF_XCAST_MODE_ALLMULTI 134 
#define  IXGBEVF_XCAST_MODE_MULTI 133 
#define  IXGBEVF_XCAST_MODE_NONE 132 
#define  IXGBEVF_XCAST_MODE_PROMISC 131 
 int /*<<< orphan*/  IXGBE_FCTRL ; 
 size_t IXGBE_FCTRL_UPE ; 
 size_t IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VMOLR (size_t) ; 
 size_t IXGBE_VMOLR_BAM ; 
 size_t IXGBE_VMOLR_MPE ; 
 size_t IXGBE_VMOLR_ROMPE ; 
 size_t IXGBE_VMOLR_UPE ; 
 size_t IXGBE_VMOLR_VPE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixgbe_mac_82599EB ; 
#define  ixgbe_mbox_api_12 130 
#define  ixgbe_mbox_api_13 129 
#define  ixgbe_mbox_api_14 128 

__attribute__((used)) static int ixgbe_update_vf_xcast_mode(struct ixgbe_adapter *adapter,
				      u32 *msgbuf, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int xcast_mode = msgbuf[1];
	u32 vmolr, fctrl, disable, enable;

	/* verify the PF is supporting the correct APIs */
	switch (adapter->vfinfo[vf].vf_api) {
	case ixgbe_mbox_api_12:
		/* promisc introduced in 1.3 version */
		if (xcast_mode == IXGBEVF_XCAST_MODE_PROMISC)
			return -EOPNOTSUPP;
		/* Fall through */
	case ixgbe_mbox_api_13:
	case ixgbe_mbox_api_14:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (xcast_mode > IXGBEVF_XCAST_MODE_MULTI &&
	    !adapter->vfinfo[vf].trusted) {
		xcast_mode = IXGBEVF_XCAST_MODE_MULTI;
	}

	if (adapter->vfinfo[vf].xcast_mode == xcast_mode)
		goto out;

	switch (xcast_mode) {
	case IXGBEVF_XCAST_MODE_NONE:
		disable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE |
			  IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = 0;
		break;
	case IXGBEVF_XCAST_MODE_MULTI:
		disable = IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE;
		break;
	case IXGBEVF_XCAST_MODE_ALLMULTI:
		disable = IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE | IXGBE_VMOLR_MPE;
		break;
	case IXGBEVF_XCAST_MODE_PROMISC:
		if (hw->mac.type <= ixgbe_mac_82599EB)
			return -EOPNOTSUPP;

		fctrl = IXGBE_READ_REG(hw, IXGBE_FCTRL);
		if (!(fctrl & IXGBE_FCTRL_UPE)) {
			/* VF promisc requires PF in promisc */
			e_warn(drv,
			       "Enabling VF promisc requires PF in promisc\n");
			return -EPERM;
		}

		disable = 0;
		enable = IXGBE_VMOLR_BAM | IXGBE_VMOLR_ROMPE |
			 IXGBE_VMOLR_MPE | IXGBE_VMOLR_UPE | IXGBE_VMOLR_VPE;
		break;
	default:
		return -EOPNOTSUPP;
	}

	vmolr = IXGBE_READ_REG(hw, IXGBE_VMOLR(vf));
	vmolr &= ~disable;
	vmolr |= enable;
	IXGBE_WRITE_REG(hw, IXGBE_VMOLR(vf), vmolr);

	adapter->vfinfo[vf].xcast_mode = xcast_mode;

out:
	msgbuf[1] = xcast_mode;

	return 0;
}