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
struct ethtool_flow_ext {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_DIST_ETHDST ; 
 int /*<<< orphan*/  NET_PROT_ETH ; 
 int /*<<< orphan*/  NH_FLD_ETH_DA ; 
 int dpaa2_eth_cls_fld_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prep_mac_ext_rule(struct ethtool_flow_ext *ext_value,
			     struct ethtool_flow_ext *ext_mask,
			     void *key, void *mask, u64 *fields)
{
	int off;

	if (!is_zero_ether_addr(ext_mask->h_dest)) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_DA);
		ether_addr_copy(key + off, ext_value->h_dest);
		ether_addr_copy(mask + off, ext_mask->h_dest);
		*fields |= DPAA2_ETH_DIST_ETHDST;
	}

	return 0;
}