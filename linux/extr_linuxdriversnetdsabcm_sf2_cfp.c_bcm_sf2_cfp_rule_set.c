#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__* data; scalar_t__ vlan_etype; } ;
struct ethtool_rx_flow_spec {unsigned int ring_cookie; int flow_type; scalar_t__ location; TYPE_3__ m_ext; } ;
struct dsa_switch {TYPE_2__* ports; } ;
struct TYPE_10__ {unsigned int num_ports; } ;
struct TYPE_9__ {int /*<<< orphan*/  used; } ;
struct bcm_sf2_priv {TYPE_5__ hw_params; TYPE_4__ cfp; } ;
typedef  unsigned int s8 ;
typedef  unsigned int __u64 ;
struct TYPE_7__ {TYPE_1__* cpu_dp; } ;
struct TYPE_6__ {unsigned int index; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int FLOW_EXT ; 
 unsigned int RX_CLS_FLOW_DISC ; 
 unsigned int RX_CLS_FLOW_WAKE ; 
 scalar_t__ RX_CLS_LOC_ANY ; 
 unsigned int SF2_NUM_EGRESS_QUEUES ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int bcm_sf2_cfp_ipv4_rule_set (struct bcm_sf2_priv*,int,unsigned int,unsigned int,struct ethtool_rx_flow_spec*) ; 
 int bcm_sf2_cfp_ipv6_rule_set (struct bcm_sf2_priv*,int,unsigned int,unsigned int,struct ethtool_rx_flow_spec*) ; 
 scalar_t__ bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,unsigned int) ; 
 scalar_t__ dsa_is_user_port (struct dsa_switch*,unsigned int) ; 
 scalar_t__ test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_rule_set(struct dsa_switch *ds, int port,
				struct ethtool_rx_flow_spec *fs)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	s8 cpu_port = ds->ports[port].cpu_dp->index;
	__u64 ring_cookie = fs->ring_cookie;
	unsigned int queue_num, port_num;
	int ret = -EINVAL;

	/* Check for unsupported extensions */
	if ((fs->flow_type & FLOW_EXT) && (fs->m_ext.vlan_etype ||
	     fs->m_ext.data[1]))
		return -EINVAL;

	if (fs->location != RX_CLS_LOC_ANY &&
	    test_bit(fs->location, priv->cfp.used))
		return -EBUSY;

	if (fs->location != RX_CLS_LOC_ANY &&
	    fs->location > bcm_sf2_cfp_rule_size(priv))
		return -EINVAL;

	/* This rule is a Wake-on-LAN filter and we must specifically
	 * target the CPU port in order for it to be working.
	 */
	if (ring_cookie == RX_CLS_FLOW_WAKE)
		ring_cookie = cpu_port * SF2_NUM_EGRESS_QUEUES;

	/* We do not support discarding packets, check that the
	 * destination port is enabled and that we are within the
	 * number of ports supported by the switch
	 */
	port_num = ring_cookie / SF2_NUM_EGRESS_QUEUES;

	if (ring_cookie == RX_CLS_FLOW_DISC ||
	    !(dsa_is_user_port(ds, port_num) ||
	      dsa_is_cpu_port(ds, port_num)) ||
	    port_num >= priv->hw_params.num_ports)
		return -EINVAL;
	/*
	 * We have a small oddity where Port 6 just does not have a
	 * valid bit here (so we substract by one).
	 */
	queue_num = ring_cookie % SF2_NUM_EGRESS_QUEUES;
	if (port_num >= 7)
		port_num -= 1;

	switch (fs->flow_type & ~FLOW_EXT) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
		ret = bcm_sf2_cfp_ipv4_rule_set(priv, port, port_num,
						queue_num, fs);
		break;
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
		ret = bcm_sf2_cfp_ipv6_rule_set(priv, port, port_num,
						queue_num, fs);
		break;
	default:
		break;
	}

	return ret;
}