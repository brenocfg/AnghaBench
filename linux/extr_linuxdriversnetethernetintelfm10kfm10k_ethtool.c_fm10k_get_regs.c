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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int type; int max_queues; } ;
struct fm10k_hw {int revision_id; int device_id; TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;
struct ethtool_regs {int version; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  FM10K_CTRL ; 
 int /*<<< orphan*/  FM10K_CTRL_EXT ; 
 int /*<<< orphan*/  FM10K_DGLORTDEC (int) ; 
 int /*<<< orphan*/  FM10K_DGLORTMAP (int) ; 
 int /*<<< orphan*/  FM10K_DMA_CTRL ; 
 int /*<<< orphan*/  FM10K_DMA_CTRL2 ; 
 int /*<<< orphan*/  FM10K_GCR ; 
 int /*<<< orphan*/  FM10K_GCR_EXT ; 
 int /*<<< orphan*/  FM10K_INT_MAP (int) ; 
 int /*<<< orphan*/  FM10K_ITR (int) ; 
 int FM10K_MAX_QUEUES_PF ; 
 int FM10K_MAX_QUEUES_POOL ; 
 int FM10K_REGS_LEN_Q ; 
 int /*<<< orphan*/  FM10K_REGS_LEN_VSI ; 
 int /*<<< orphan*/  FM10K_TPH_CTRL ; 
 int /*<<< orphan*/  FM10K_VFCTRL ; 
 int /*<<< orphan*/  FM10K_VFINT_MAP ; 
 int /*<<< orphan*/  FM10K_VFITR (int) ; 
 int /*<<< orphan*/  FM10K_VFSYSTIME ; 
 int /*<<< orphan*/  fm10k_get_reg_q (struct fm10k_hw*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fm10k_get_reg_vsi (struct fm10k_hw*,int /*<<< orphan*/ *,int) ; 
#define  fm10k_mac_pf 129 
#define  fm10k_mac_vf 128 
 void* fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void fm10k_get_regs(struct net_device *netdev,
			   struct ethtool_regs *regs, void *p)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_hw *hw = &interface->hw;
	u32 *buff = p;
	u16 i;

	regs->version = BIT(24) | (hw->revision_id << 16) | hw->device_id;

	switch (hw->mac.type) {
	case fm10k_mac_pf:
		/* General PF Registers */
		*(buff++) = fm10k_read_reg(hw, FM10K_CTRL);
		*(buff++) = fm10k_read_reg(hw, FM10K_CTRL_EXT);
		*(buff++) = fm10k_read_reg(hw, FM10K_GCR);
		*(buff++) = fm10k_read_reg(hw, FM10K_GCR_EXT);

		for (i = 0; i < 8; i++) {
			*(buff++) = fm10k_read_reg(hw, FM10K_DGLORTMAP(i));
			*(buff++) = fm10k_read_reg(hw, FM10K_DGLORTDEC(i));
		}

		for (i = 0; i < 65; i++) {
			fm10k_get_reg_vsi(hw, buff, i);
			buff += FM10K_REGS_LEN_VSI;
		}

		*(buff++) = fm10k_read_reg(hw, FM10K_DMA_CTRL);
		*(buff++) = fm10k_read_reg(hw, FM10K_DMA_CTRL2);

		for (i = 0; i < FM10K_MAX_QUEUES_PF; i++) {
			fm10k_get_reg_q(hw, buff, i);
			buff += FM10K_REGS_LEN_Q;
		}

		*(buff++) = fm10k_read_reg(hw, FM10K_TPH_CTRL);

		for (i = 0; i < 8; i++)
			*(buff++) = fm10k_read_reg(hw, FM10K_INT_MAP(i));

		/* Interrupt Throttling Registers */
		for (i = 0; i < 130; i++)
			*(buff++) = fm10k_read_reg(hw, FM10K_ITR(i));

		break;
	case fm10k_mac_vf:
		/* General VF registers */
		*(buff++) = fm10k_read_reg(hw, FM10K_VFCTRL);
		*(buff++) = fm10k_read_reg(hw, FM10K_VFINT_MAP);
		*(buff++) = fm10k_read_reg(hw, FM10K_VFSYSTIME);

		/* Interrupt Throttling Registers */
		for (i = 0; i < 8; i++)
			*(buff++) = fm10k_read_reg(hw, FM10K_VFITR(i));

		fm10k_get_reg_vsi(hw, buff, 0);
		buff += FM10K_REGS_LEN_VSI;

		for (i = 0; i < FM10K_MAX_QUEUES_POOL; i++) {
			if (i < hw->mac.max_queues)
				fm10k_get_reg_q(hw, buff, i);
			else
				memset(buff, 0, sizeof(u32) * FM10K_REGS_LEN_Q);
			buff += FM10K_REGS_LEN_Q;
		}

		break;
	default:
		return;
	}
}