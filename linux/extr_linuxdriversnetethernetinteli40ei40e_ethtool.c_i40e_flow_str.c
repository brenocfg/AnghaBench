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
struct ethtool_rx_flow_spec {int flow_type; } ;

/* Variables and functions */
 int FLOW_EXT ; 
#define  IP_USER_FLOW 131 
#define  SCTP_V4_FLOW 130 
#define  TCP_V4_FLOW 129 
#define  UDP_V4_FLOW 128 

__attribute__((used)) static const char *i40e_flow_str(struct ethtool_rx_flow_spec *fsp)
{
	switch (fsp->flow_type & ~FLOW_EXT) {
	case TCP_V4_FLOW:
		return "tcp4";
	case UDP_V4_FLOW:
		return "udp4";
	case SCTP_V4_FLOW:
		return "sctp4";
	case IP_USER_FLOW:
		return "ip4";
	default:
		return "unknown";
	}
}