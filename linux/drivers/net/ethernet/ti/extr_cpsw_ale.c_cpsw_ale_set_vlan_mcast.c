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
struct TYPE_2__ {scalar_t__ ale_regs; } ;
struct cpsw_ale {TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ ALE_VLAN_MASK_MUX (int) ; 
 int cpsw_ale_get_vlan_reg_mcast_idx (int /*<<< orphan*/ *) ; 
 int cpsw_ale_get_vlan_unreg_mcast_idx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cpsw_ale_set_vlan_mcast(struct cpsw_ale *ale, u32 *ale_entry,
				    int reg_mcast, int unreg_mcast)
{
	int idx;

	/* Set VLAN registered multicast flood mask */
	idx = cpsw_ale_get_vlan_reg_mcast_idx(ale_entry);
	writel(reg_mcast, ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));

	/* Set VLAN unregistered multicast flood mask */
	idx = cpsw_ale_get_vlan_unreg_mcast_idx(ale_entry);
	writel(unreg_mcast, ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));
}