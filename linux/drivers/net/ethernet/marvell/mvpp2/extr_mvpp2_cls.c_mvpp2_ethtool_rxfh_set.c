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
typedef  int u32 ;
typedef  int u16 ;
struct mvpp2_port {int dummy; } ;
struct ethtool_rxnfc {int data; int /*<<< orphan*/  flow_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MVPP22_CLS_HEK_OPT_IP4DA ; 
 int MVPP22_CLS_HEK_OPT_IP4SA ; 
 int MVPP22_CLS_HEK_OPT_IP6DA ; 
 int MVPP22_CLS_HEK_OPT_IP6SA ; 
 int MVPP22_CLS_HEK_OPT_L3_PROTO ; 
 int MVPP22_CLS_HEK_OPT_L4DIP ; 
 int MVPP22_CLS_HEK_OPT_L4SIP ; 
 int MVPP22_CLS_HEK_OPT_MAC_DA ; 
 int MVPP22_CLS_HEK_OPT_VLAN ; 
#define  MVPP22_FLOW_IP4 133 
#define  MVPP22_FLOW_IP6 132 
#define  MVPP22_FLOW_TCP4 131 
#define  MVPP22_FLOW_TCP6 130 
#define  MVPP22_FLOW_UDP4 129 
#define  MVPP22_FLOW_UDP6 128 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L2DA ; 
 int RXH_L3_PROTO ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 int RXH_VLAN ; 
 int mvpp2_cls_ethtool_flow_to_type (int /*<<< orphan*/ ) ; 
 int mvpp2_port_rss_hash_opts_set (struct mvpp2_port*,int,int) ; 

int mvpp2_ethtool_rxfh_set(struct mvpp2_port *port, struct ethtool_rxnfc *info)
{
	u16 hash_opts = 0;
	u32 flow_type;

	flow_type = mvpp2_cls_ethtool_flow_to_type(info->flow_type);

	switch (flow_type) {
	case MVPP22_FLOW_TCP4:
	case MVPP22_FLOW_UDP4:
	case MVPP22_FLOW_TCP6:
	case MVPP22_FLOW_UDP6:
		if (info->data & RXH_L4_B_0_1)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4SIP;
		if (info->data & RXH_L4_B_2_3)
			hash_opts |= MVPP22_CLS_HEK_OPT_L4DIP;
		/* Fallthrough */
	case MVPP22_FLOW_IP4:
	case MVPP22_FLOW_IP6:
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

	return mvpp2_port_rss_hash_opts_set(port, flow_type, hash_opts);
}