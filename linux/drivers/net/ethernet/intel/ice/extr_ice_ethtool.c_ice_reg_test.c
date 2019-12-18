#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct ice_diag_reg_test_info   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ice_netdev_priv {TYPE_2__* vsi; } ;
struct TYPE_8__ {int num_msix_vectors; } ;
struct TYPE_9__ {TYPE_3__ common_cap; } ;
struct ice_hw {TYPE_4__ func_caps; } ;
struct ice_diag_reg_test_info {int address; int mask; int elem_num; int elem_size; } ;
struct TYPE_7__ {TYPE_1__* port_info; } ;
struct TYPE_6__ {struct ice_hw* hw; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_5__*) ; 
 scalar_t__ GLINT_CTL ; 
 scalar_t__ GLINT_ITR (int,int) ; 
 scalar_t__ ice_reg_pattern_test (struct ice_hw*,int,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u64 ice_reg_test(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_hw *hw = np->vsi->port_info->hw;
	u32 int_elements = hw->func_caps.common_cap.num_msix_vectors ?
		hw->func_caps.common_cap.num_msix_vectors - 1 : 1;
	struct ice_diag_reg_test_info {
		u32 address;
		u32 mask;
		u32 elem_num;
		u32 elem_size;
	} ice_reg_list[] = {
		{GLINT_ITR(0, 0), 0x00000fff, int_elements,
			GLINT_ITR(0, 1) - GLINT_ITR(0, 0)},
		{GLINT_ITR(1, 0), 0x00000fff, int_elements,
			GLINT_ITR(1, 1) - GLINT_ITR(1, 0)},
		{GLINT_ITR(0, 0), 0x00000fff, int_elements,
			GLINT_ITR(2, 1) - GLINT_ITR(2, 0)},
		{GLINT_CTL, 0xffff0001, 1, 0}
	};
	int i;

	netdev_dbg(netdev, "Register test\n");
	for (i = 0; i < ARRAY_SIZE(ice_reg_list); ++i) {
		u32 j;

		for (j = 0; j < ice_reg_list[i].elem_num; ++j) {
			u32 mask = ice_reg_list[i].mask;
			u32 reg = ice_reg_list[i].address +
				(j * ice_reg_list[i].elem_size);

			/* bail on failure (non-zero return) */
			if (ice_reg_pattern_test(hw, reg, mask))
				return 1;
		}
	}

	return 0;
}