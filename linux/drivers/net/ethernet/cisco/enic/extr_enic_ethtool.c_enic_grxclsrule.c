#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ethtool_rxnfc {int /*<<< orphan*/  fs; } ;
struct TYPE_13__ {void* pdst; void* psrc; void* ip4dst; void* ip4src; } ;
struct TYPE_14__ {TYPE_5__ tcp_ip4_spec; } ;
struct TYPE_10__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_11__ {TYPE_2__ tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {int /*<<< orphan*/  ring_cookie; TYPE_6__ m_u; TYPE_3__ h_u; int /*<<< orphan*/  flow_type; scalar_t__ location; } ;
struct TYPE_12__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_9__ {int ip_proto; } ;
struct TYPE_15__ {TYPE_4__ ports; TYPE_1__ basic; } ;
struct enic_rfs_fltr_node {int /*<<< orphan*/  rq_id; TYPE_7__ keys; } ;
struct enic {int dummy; } ;
typedef  void* __u32 ;
typedef  void* __u16 ;

/* Variables and functions */
 int EINVAL ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  TCP_V4_FLOW ; 
 int /*<<< orphan*/  UDP_V4_FLOW ; 
 int /*<<< orphan*/  flow_get_u32_dst (TYPE_7__*) ; 
 int /*<<< orphan*/  flow_get_u32_src (TYPE_7__*) ; 
 struct enic_rfs_fltr_node* htbl_fltr_search (struct enic*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_grxclsrule(struct enic *enic, struct ethtool_rxnfc *cmd)
{
	struct ethtool_rx_flow_spec *fsp =
				(struct ethtool_rx_flow_spec *)&cmd->fs;
	struct enic_rfs_fltr_node *n;

	n = htbl_fltr_search(enic, (u16)fsp->location);
	if (!n)
		return -EINVAL;
	switch (n->keys.basic.ip_proto) {
	case IPPROTO_TCP:
		fsp->flow_type = TCP_V4_FLOW;
		break;
	case IPPROTO_UDP:
		fsp->flow_type = UDP_V4_FLOW;
		break;
	default:
		return -EINVAL;
		break;
	}

	fsp->h_u.tcp_ip4_spec.ip4src = flow_get_u32_src(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4src = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.ip4dst = flow_get_u32_dst(&n->keys);
	fsp->m_u.tcp_ip4_spec.ip4dst = (__u32)~0;

	fsp->h_u.tcp_ip4_spec.psrc = n->keys.ports.src;
	fsp->m_u.tcp_ip4_spec.psrc = (__u16)~0;

	fsp->h_u.tcp_ip4_spec.pdst = n->keys.ports.dst;
	fsp->m_u.tcp_ip4_spec.pdst = (__u16)~0;

	fsp->ring_cookie = n->rq_id;

	return 0;
}