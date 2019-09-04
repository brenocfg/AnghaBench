#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vfpf_q_mac_vlan_filter {int flags; int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan_tag; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int,char*,int,int) ; 
 int /*<<< orphan*/  DP_CONT (int,char*,...) ; 
 int VFPF_Q_FILTER_DEST_MAC_VALID ; 
 int VFPF_Q_FILTER_VLAN_TAG_VALID ; 

__attribute__((used)) static void bnx2x_vf_mbx_dp_q_filter(struct bnx2x *bp, int msglvl, int idx,
				       struct vfpf_q_mac_vlan_filter *filter)
{
	DP(msglvl, "MAC-VLAN[%d] -- flags=0x%x\n", idx, filter->flags);
	if (filter->flags & VFPF_Q_FILTER_VLAN_TAG_VALID)
		DP_CONT(msglvl, ", vlan=%d", filter->vlan_tag);
	if (filter->flags & VFPF_Q_FILTER_DEST_MAC_VALID)
		DP_CONT(msglvl, ", MAC=%pM", filter->mac);
	DP_CONT(msglvl, "\n");
}