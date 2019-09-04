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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {int flags; } ;
struct eth_fast_path_rx_reg_cqe {TYPE_1__ tunnel_pars_flags; } ;

/* Variables and functions */
 int ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_MASK ; 
 int ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_SHIFT ; 
 int PARSING_AND_ERR_FLAGS_IPV4FRAG_MASK ; 
 int PARSING_AND_ERR_FLAGS_IPV4FRAG_SHIFT ; 

__attribute__((used)) static bool qede_pkt_is_ip_fragmented(struct eth_fast_path_rx_reg_cqe *cqe,
				      u16 flag)
{
	u8 tun_pars_flg = cqe->tunnel_pars_flags.flags;

	if ((tun_pars_flg & (ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_MASK <<
			     ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_SHIFT)) ||
	    (flag & (PARSING_AND_ERR_FLAGS_IPV4FRAG_MASK <<
		     PARSING_AND_ERR_FLAGS_IPV4FRAG_SHIFT)))
		return true;

	return false;
}