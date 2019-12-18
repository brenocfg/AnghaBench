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
typedef  int /*<<< orphan*/  u64 ;
struct ethtool_flow_ext {scalar_t__ vlan_tci; scalar_t__ vlan_etype; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_DIST_VLAN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NET_PROT_VLAN ; 
 int /*<<< orphan*/  NH_FLD_VLAN_TCI ; 
 int dpaa2_eth_cls_fld_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prep_ext_rule(struct ethtool_flow_ext *ext_value,
			 struct ethtool_flow_ext *ext_mask,
			 void *key, void *mask, u64 *fields)
{
	int off;

	if (ext_mask->vlan_etype)
		return -EOPNOTSUPP;

	if (ext_mask->vlan_tci) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_VLAN, NH_FLD_VLAN_TCI);
		*(__be16 *)(key + off) = ext_value->vlan_tci;
		*(__be16 *)(mask + off) = ext_mask->vlan_tci;
		*fields |= DPAA2_ETH_DIST_VLAN;
	}

	return 0;
}