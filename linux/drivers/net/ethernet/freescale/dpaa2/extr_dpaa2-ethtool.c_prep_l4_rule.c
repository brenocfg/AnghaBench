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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ethtool_tcpip4_spec {scalar_t__ pdst; scalar_t__ psrc; scalar_t__ ip4dst; scalar_t__ ip4src; scalar_t__ tos; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA2_ETH_DIST_ETHTYPE ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_IPDST ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_IPPROTO ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_IPSRC ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_L4DST ; 
 int /*<<< orphan*/  DPAA2_ETH_DIST_L4SRC ; 
 int EOPNOTSUPP ; 
 int ETH_P_IP ; 
 int /*<<< orphan*/  NET_PROT_ETH ; 
 int /*<<< orphan*/  NET_PROT_IP ; 
 int /*<<< orphan*/  NET_PROT_UDP ; 
 int /*<<< orphan*/  NH_FLD_ETH_TYPE ; 
 int /*<<< orphan*/  NH_FLD_IP_DST ; 
 int /*<<< orphan*/  NH_FLD_IP_PROTO ; 
 int /*<<< orphan*/  NH_FLD_IP_SRC ; 
 int /*<<< orphan*/  NH_FLD_UDP_PORT_DST ; 
 int /*<<< orphan*/  NH_FLD_UDP_PORT_SRC ; 
 int dpaa2_eth_cls_fld_off (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 

__attribute__((used)) static int prep_l4_rule(struct ethtool_tcpip4_spec *l4_value,
			struct ethtool_tcpip4_spec *l4_mask,
			void *key, void *mask, u8 l4_proto, u64 *fields)
{
	int off;

	if (l4_mask->tos)
		return -EOPNOTSUPP;

	if (l4_mask->ip4src) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_SRC);
		*(__be32 *)(key + off) = l4_value->ip4src;
		*(__be32 *)(mask + off) = l4_mask->ip4src;
		*fields |= DPAA2_ETH_DIST_IPSRC;
	}

	if (l4_mask->ip4dst) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_DST);
		*(__be32 *)(key + off) = l4_value->ip4dst;
		*(__be32 *)(mask + off) = l4_mask->ip4dst;
		*fields |= DPAA2_ETH_DIST_IPDST;
	}

	if (l4_mask->psrc) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_SRC);
		*(__be16 *)(key + off) = l4_value->psrc;
		*(__be16 *)(mask + off) = l4_mask->psrc;
		*fields |= DPAA2_ETH_DIST_L4SRC;
	}

	if (l4_mask->pdst) {
		off = dpaa2_eth_cls_fld_off(NET_PROT_UDP, NH_FLD_UDP_PORT_DST);
		*(__be16 *)(key + off) = l4_value->pdst;
		*(__be16 *)(mask + off) = l4_mask->pdst;
		*fields |= DPAA2_ETH_DIST_L4DST;
	}

	/* Only apply the rule for IPv4 frames with the specified L4 proto */
	off = dpaa2_eth_cls_fld_off(NET_PROT_ETH, NH_FLD_ETH_TYPE);
	*(__be16 *)(key + off) = htons(ETH_P_IP);
	*(__be16 *)(mask + off) = htons(0xFFFF);
	*fields |= DPAA2_ETH_DIST_ETHTYPE;

	off = dpaa2_eth_cls_fld_off(NET_PROT_IP, NH_FLD_IP_PROTO);
	*(u8 *)(key + off) = l4_proto;
	*(u8 *)(mask + off) = 0xFF;
	*fields |= DPAA2_ETH_DIST_IPPROTO;

	return 0;
}