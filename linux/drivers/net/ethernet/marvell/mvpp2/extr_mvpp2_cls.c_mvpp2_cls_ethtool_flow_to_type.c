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
 int EOPNOTSUPP ; 
#define  ETHER_FLOW 134 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
 int FLOW_RSS ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int MVPP22_FLOW_ETHERNET ; 
 int MVPP22_FLOW_IP4 ; 
 int MVPP22_FLOW_IP6 ; 
 int MVPP22_FLOW_TCP4 ; 
 int MVPP22_FLOW_TCP6 ; 
 int MVPP22_FLOW_UDP4 ; 
 int MVPP22_FLOW_UDP6 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static int mvpp2_cls_ethtool_flow_to_type(int flow_type)
{
	switch (flow_type & ~(FLOW_EXT | FLOW_MAC_EXT | FLOW_RSS)) {
	case ETHER_FLOW:
		return MVPP22_FLOW_ETHERNET;
	case TCP_V4_FLOW:
		return MVPP22_FLOW_TCP4;
	case TCP_V6_FLOW:
		return MVPP22_FLOW_TCP6;
	case UDP_V4_FLOW:
		return MVPP22_FLOW_UDP4;
	case UDP_V6_FLOW:
		return MVPP22_FLOW_UDP6;
	case IPV4_FLOW:
		return MVPP22_FLOW_IP4;
	case IPV6_FLOW:
		return MVPP22_FLOW_IP6;
	default:
		return -EOPNOTSUPP;
	}
}