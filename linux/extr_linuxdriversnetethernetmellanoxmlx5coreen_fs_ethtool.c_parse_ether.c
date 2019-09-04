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
typedef  int /*<<< orphan*/  u8 ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct TYPE_3__ {struct ethhdr ether_spec; } ;
struct TYPE_4__ {struct ethhdr ether_spec; } ;
struct ethtool_rx_flow_spec {TYPE_1__ h_u; TYPE_2__ m_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_FTE_ADDR_OF (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_FTE_SET (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmac_47_16 ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype ; 
 int /*<<< orphan*/  mask_spec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smac_47_16 ; 

__attribute__((used)) static void
parse_ether(void *headers_c, void *headers_v, struct ethtool_rx_flow_spec *fs)
{
	struct ethhdr *eth_mask = &fs->m_u.ether_spec;
	struct ethhdr *eth_val = &fs->h_u.ether_spec;

	mask_spec((u8 *)eth_mask, (u8 *)eth_val, sizeof(*eth_mask));
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_c, smac_47_16), eth_mask->h_source);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_v, smac_47_16), eth_val->h_source);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_c, dmac_47_16), eth_mask->h_dest);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_v, dmac_47_16), eth_val->h_dest);
	MLX5E_FTE_SET(headers_c, ethertype, ntohs(eth_mask->h_proto));
	MLX5E_FTE_SET(headers_v, ethertype, ntohs(eth_val->h_proto));
}