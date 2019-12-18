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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  sctp_ip4_spec; int /*<<< orphan*/  udp_ip4_spec; int /*<<< orphan*/  tcp_ip4_spec; int /*<<< orphan*/  usr_ip4_spec; int /*<<< orphan*/  ether_spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  sctp_ip4_spec; int /*<<< orphan*/  udp_ip4_spec; int /*<<< orphan*/  tcp_ip4_spec; int /*<<< orphan*/  usr_ip4_spec; int /*<<< orphan*/  ether_spec; } ;
struct ethtool_rx_flow_spec {int flow_type; int /*<<< orphan*/  m_ext; int /*<<< orphan*/  h_ext; TYPE_2__ m_u; TYPE_1__ h_u; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHER_FLOW 132 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
#define  IP_USER_FLOW 131 
#define  SCTP_V4_FLOW 130 
#define  TCP_V4_FLOW 129 
#define  UDP_V4_FLOW 128 
 int prep_eth_rule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 int prep_ext_rule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 int prep_l4_rule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int prep_mac_ext_rule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 
 int prep_uip_rule (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int prep_cls_rule(struct ethtool_rx_flow_spec *fs, void *key, void *mask,
			 u64 *fields)
{
	int err;

	switch (fs->flow_type & 0xFF) {
	case ETHER_FLOW:
		err = prep_eth_rule(&fs->h_u.ether_spec, &fs->m_u.ether_spec,
				    key, mask, fields);
		break;
	case IP_USER_FLOW:
		err = prep_uip_rule(&fs->h_u.usr_ip4_spec,
				    &fs->m_u.usr_ip4_spec, key, mask, fields);
		break;
	case TCP_V4_FLOW:
		err = prep_l4_rule(&fs->h_u.tcp_ip4_spec, &fs->m_u.tcp_ip4_spec,
				   key, mask, IPPROTO_TCP, fields);
		break;
	case UDP_V4_FLOW:
		err = prep_l4_rule(&fs->h_u.udp_ip4_spec, &fs->m_u.udp_ip4_spec,
				   key, mask, IPPROTO_UDP, fields);
		break;
	case SCTP_V4_FLOW:
		err = prep_l4_rule(&fs->h_u.sctp_ip4_spec,
				   &fs->m_u.sctp_ip4_spec, key, mask,
				   IPPROTO_SCTP, fields);
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (err)
		return err;

	if (fs->flow_type & FLOW_EXT) {
		err = prep_ext_rule(&fs->h_ext, &fs->m_ext, key, mask, fields);
		if (err)
			return err;
	}

	if (fs->flow_type & FLOW_MAC_EXT) {
		err = prep_mac_ext_rule(&fs->h_ext, &fs->m_ext, key, mask,
					fields);
		if (err)
			return err;
	}

	return 0;
}