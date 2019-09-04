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
typedef  int u16 ;
struct mvpp2_port {int dummy; } ;
struct ethtool_rxnfc {int flow_type; int data; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int MVPP22_CLS_HEK_OPT_IP4DA ; 
 int MVPP22_CLS_HEK_OPT_IP4SA ; 
 int MVPP22_CLS_HEK_OPT_IP6DA ; 
 int MVPP22_CLS_HEK_OPT_IP6SA ; 
 int MVPP22_CLS_HEK_OPT_L3_PROTO ; 
 int MVPP22_CLS_HEK_OPT_L4DIP ; 
 int MVPP22_CLS_HEK_OPT_L4SIP ; 
 int MVPP22_CLS_HEK_OPT_MAC_DA ; 
 int MVPP22_CLS_HEK_OPT_VLAN ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L2DA ; 
 int RXH_L3_PROTO ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 int RXH_VLAN ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int mvpp2_port_rss_hash_opts_set (struct mvpp2_port*,int,int) ; 

int mvpp2_ethtool_rxfh_set(struct mvpp2_port *port, struct ethtool_rxnfc *info)
{
	u16 hash_opts = 0;

	switch (info->flow_type) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
		if (info->data & RXH_L4_B_0_1)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4SIP;
		if (info->data & RXH_L4_B_2_3)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4DIP;
		/* Fallthrough */
	case IPV4_FLOW:
	case IPV6_FLOW:
		if (info->data & RXH_L2DA)
			hash_opts |= MVPP22_CLS_HEK_OPT_MAC_DA;
		if (info->data & RXH_VLAN)
			hash_opts |= MVPP22_CLS_HEK_OPT_VLAN;
		if (info->data & RXH_L3_PROTO)
			hash_opts |= MVPP22_CLS_HEK_OPT_L3_PROTO;
		if (info->data & RXH_IP_SRC)
			hash_opts |= (MVPP22_CLS_HEK_OPT_IP4SA |
				     MVPP22_CLS_HEK_OPT_IP6SA);
		if (info->data & RXH_IP_DST)
			hash_opts |= (MVPP22_CLS_HEK_OPT_IP4DA |
				     MVPP22_CLS_HEK_OPT_IP6DA);
		break;
	default: return -EOPNOTSUPP;
	}

	return mvpp2_port_rss_hash_opts_set(port, info->flow_type, hash_opts);
}