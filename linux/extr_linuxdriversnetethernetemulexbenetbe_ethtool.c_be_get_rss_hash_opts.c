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
typedef  int u64 ;
struct TYPE_2__ {int rss_flags; } ;
struct be_adapter {TYPE_1__ rss_info; } ;

/* Variables and functions */
 int RSS_ENABLE_IPV4 ; 
 int RSS_ENABLE_IPV6 ; 
 int RSS_ENABLE_TCP_IPV4 ; 
 int RSS_ENABLE_TCP_IPV6 ; 
 int RSS_ENABLE_UDP_IPV4 ; 
 int RSS_ENABLE_UDP_IPV6 ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static u64 be_get_rss_hash_opts(struct be_adapter *adapter, u64 flow_type)
{
	u64 data = 0;

	switch (flow_type) {
	case TCP_V4_FLOW:
		if (adapter->rss_info.rss_flags & RSS_ENABLE_IPV4)
			data |= RXH_IP_DST | RXH_IP_SRC;
		if (adapter->rss_info.rss_flags & RSS_ENABLE_TCP_IPV4)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case UDP_V4_FLOW:
		if (adapter->rss_info.rss_flags & RSS_ENABLE_IPV4)
			data |= RXH_IP_DST | RXH_IP_SRC;
		if (adapter->rss_info.rss_flags & RSS_ENABLE_UDP_IPV4)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case TCP_V6_FLOW:
		if (adapter->rss_info.rss_flags & RSS_ENABLE_IPV6)
			data |= RXH_IP_DST | RXH_IP_SRC;
		if (adapter->rss_info.rss_flags & RSS_ENABLE_TCP_IPV6)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case UDP_V6_FLOW:
		if (adapter->rss_info.rss_flags & RSS_ENABLE_IPV6)
			data |= RXH_IP_DST | RXH_IP_SRC;
		if (adapter->rss_info.rss_flags & RSS_ENABLE_UDP_IPV6)
			data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	}

	return data;
}