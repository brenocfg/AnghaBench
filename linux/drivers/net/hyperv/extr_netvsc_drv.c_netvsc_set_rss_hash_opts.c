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
struct net_device_context {int /*<<< orphan*/  l4_hash; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HV_TCP4_L4HASH ; 
 int /*<<< orphan*/  HV_TCP6_L4HASH ; 
 int /*<<< orphan*/  HV_UDP4_L4HASH ; 
 int /*<<< orphan*/  HV_UDP6_L4HASH ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static int netvsc_set_rss_hash_opts(struct net_device_context *ndc,
				    struct ethtool_rxnfc *info)
{
	if (info->data == (RXH_IP_SRC | RXH_IP_DST |
			   RXH_L4_B_0_1 | RXH_L4_B_2_3)) {
		switch (info->flow_type) {
		case TCP_V4_FLOW:
			ndc->l4_hash |= HV_TCP4_L4HASH;
			break;

		case TCP_V6_FLOW:
			ndc->l4_hash |= HV_TCP6_L4HASH;
			break;

		case UDP_V4_FLOW:
			ndc->l4_hash |= HV_UDP4_L4HASH;
			break;

		case UDP_V6_FLOW:
			ndc->l4_hash |= HV_UDP6_L4HASH;
			break;

		default:
			return -EOPNOTSUPP;
		}

		return 0;
	}

	if (info->data == (RXH_IP_SRC | RXH_IP_DST)) {
		switch (info->flow_type) {
		case TCP_V4_FLOW:
			ndc->l4_hash &= ~HV_TCP4_L4HASH;
			break;

		case TCP_V6_FLOW:
			ndc->l4_hash &= ~HV_TCP6_L4HASH;
			break;

		case UDP_V4_FLOW:
			ndc->l4_hash &= ~HV_UDP4_L4HASH;
			break;

		case UDP_V6_FLOW:
			ndc->l4_hash &= ~HV_UDP6_L4HASH;
			break;

		default:
			return -EOPNOTSUPP;
		}

		return 0;
	}

	return -EOPNOTSUPP;
}