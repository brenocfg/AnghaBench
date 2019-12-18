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

/* Variables and functions */
#define  ETH_P_ATALK 134 
#define  ETH_P_IP 133 
#define  ETH_P_IPV6 132 
#define  ETH_P_IPX 131 
#define  ETH_P_MPLS_MC 130 
#define  ETH_P_MPLS_UC 129 
#define  ETH_P_PPPTALK 128 
 int NP_AT ; 
 int NP_IP ; 
 int NP_IPV6 ; 
 int NP_IPX ; 
 int NP_MPLS_MC ; 
 int NP_MPLS_UC ; 

__attribute__((used)) static inline int ethertype_to_npindex(int ethertype)
{
	switch (ethertype) {
	case ETH_P_IP:
		return NP_IP;
	case ETH_P_IPV6:
		return NP_IPV6;
	case ETH_P_IPX:
		return NP_IPX;
	case ETH_P_PPPTALK:
	case ETH_P_ATALK:
		return NP_AT;
	case ETH_P_MPLS_UC:
		return NP_MPLS_UC;
	case ETH_P_MPLS_MC:
		return NP_MPLS_MC;
	}
	return -1;
}