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
struct net_device {int dummy; } ;
struct TYPE_2__ {int type; } ;
struct fm10k_hw {TYPE_1__ mac; } ;
struct fm10k_intfc {struct fm10k_hw hw; } ;

/* Variables and functions */
 int FM10K_REGS_LEN_PF ; 
 int FM10K_REGS_LEN_VF ; 
#define  fm10k_mac_pf 129 
#define  fm10k_mac_vf 128 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int fm10k_get_regs_len(struct net_device *netdev)
{
	struct fm10k_intfc *interface = netdev_priv(netdev);
	struct fm10k_hw *hw = &interface->hw;

	switch (hw->mac.type) {
	case fm10k_mac_pf:
		return FM10K_REGS_LEN_PF * sizeof(u32);
	case fm10k_mac_vf:
		return FM10K_REGS_LEN_VF * sizeof(u32);
	default:
		return 0;
	}
}