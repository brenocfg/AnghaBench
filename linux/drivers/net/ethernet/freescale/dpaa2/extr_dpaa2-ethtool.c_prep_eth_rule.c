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
struct ethhdr {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; scalar_t__ h_proto; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_DIST_ETHDST ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_ETHSRC ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_ETHTYPE ; 
 int /*<<< orphan*/  NET_PROT_ETH ; 
 int /*<<< orphan*/  NH_FLD_ETH_DA ; 
 int /*<<< orphan*/  NH_FLD_ETH_SA ; 
 int /*<<< orphan*/  NH_FLD_ETH_TYPE ; 
 int dpaa2_eth_cls_fld_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prep_eth_rule(struct ethhdr *eth_value, struct ethhdr *eth_mask,
			 void *key, void *mask, u64 *fields)
{
	int off;

	if (eth_mask->h_proto) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_TYPE);
		*(__be16 *)(key + off) = eth_value->h_proto;
		*(__be16 *)(mask + off) = eth_mask->h_proto;
		*fields |= DPAA2_ETH_DIST_ETHTYPE;
	}

	if (!is_zero_ether_addr(eth_mask->h_source)) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_SA);
		ether_addr_copy(key + off, eth_value->h_source);
		ether_addr_copy(mask + off, eth_mask->h_source);
		*fields |= DPAA2_ETH_DIST_ETHSRC;
	}

	if (!is_zero_ether_addr(eth_mask->h_dest)) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_DA);
		ether_addr_copy(key + off, eth_value->h_dest);
		ether_addr_copy(mask + off, eth_mask->h_dest);
		*fields |= DPAA2_ETH_DIST_ETHDST;
	}

	return 0;
}