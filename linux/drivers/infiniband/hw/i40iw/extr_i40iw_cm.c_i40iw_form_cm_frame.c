#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct vlan_ethhdr {void* h_vlan_encapsulated_proto; void* h_vlan_TCI; void* h_vlan_proto; } ;
struct tcphdr {int ack; int syn; int fin; int rst; int doff; scalar_t__ urg_ptr; void* window; void* ack_seq; void* seq; void* dest; void* source; } ;
struct TYPE_10__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_11__ {TYPE_3__ in6_u; } ;
struct TYPE_8__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_9__ {TYPE_1__ in6_u; } ;
struct ipv6hdr {int version; int priority; int* flow_lbl; int nexthdr; int hop_limit; TYPE_4__ daddr; TYPE_2__ saddr; void* payload_len; } ;
struct iphdr {int ihl; int tos; int ttl; void* daddr; void* saddr; int /*<<< orphan*/  protocol; void* frag_off; void* id; void* tot_len; int /*<<< orphan*/  version; } ;
struct i40iw_sc_vsi {int /*<<< orphan*/  ilq; } ;
struct TYPE_14__ {int* va; } ;
struct i40iw_puda_buf {int totallen; int maclen; int tcphlen; int ipv4; int /*<<< orphan*/  refcount; void* scratch; TYPE_7__ mem; } ;
struct i40iw_kmem_info {int size; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {int loc_id; int loc_seq_num; int loc_ack_num; int rcv_nxt; int rcv_wnd; } ;
struct i40iw_cm_node {int vlan_id; int user_pri; int tos; int* loc_addr; int* rem_addr; int loc_port; int rem_port; TYPE_5__ tcp_cntxt; int /*<<< orphan*/  loc_mac; int /*<<< orphan*/  rem_mac; scalar_t__ ipv4; TYPE_6__* iwdev; } ;
struct ethhdr {void* h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;
struct TYPE_13__ {struct i40iw_sc_vsi vsi; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int ETH_P_8021Q ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPVERSION ; 
 int SET_ACK ; 
 int SET_FIN ; 
 int SET_RST ; 
 int SET_SYN ; 
 int VLAN_PRIO_SHIFT ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  i40iw_copy_ip_htonl (int /*<<< orphan*/ ,int*) ; 
 struct i40iw_puda_buf* i40iw_puda_get_bufpool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static struct i40iw_puda_buf *i40iw_form_cm_frame(struct i40iw_cm_node *cm_node,
						  struct i40iw_kmem_info *options,
						  struct i40iw_kmem_info *hdr,
						  struct i40iw_kmem_info *pdata,
						  u8 flags)
{
	struct i40iw_puda_buf *sqbuf;
	struct i40iw_sc_vsi *vsi = &cm_node->iwdev->vsi;
	u8 *buf;

	struct tcphdr *tcph;
	struct iphdr *iph;
	struct ipv6hdr *ip6h;
	struct ethhdr *ethh;
	u16 packetsize;
	u16 eth_hlen = ETH_HLEN;
	u32 opts_len = 0;
	u32 pd_len = 0;
	u32 hdr_len = 0;
	u16 vtag;

	sqbuf = i40iw_puda_get_bufpool(vsi->ilq);
	if (!sqbuf)
		return NULL;
	buf = sqbuf->mem.va;

	if (options)
		opts_len = (u32)options->size;

	if (hdr)
		hdr_len = hdr->size;

	if (pdata)
		pd_len = pdata->size;

	if (cm_node->vlan_id <= VLAN_VID_MASK)
		eth_hlen += 4;

	if (cm_node->ipv4)
		packetsize = sizeof(*iph) + sizeof(*tcph);
	else
		packetsize = sizeof(*ip6h) + sizeof(*tcph);
	packetsize += opts_len + hdr_len + pd_len;

	memset(buf, 0x00, eth_hlen + packetsize);

	sqbuf->totallen = packetsize + eth_hlen;
	sqbuf->maclen = eth_hlen;
	sqbuf->tcphlen = sizeof(*tcph) + opts_len;
	sqbuf->scratch = (void *)cm_node;

	ethh = (struct ethhdr *)buf;
	buf += eth_hlen;

	if (cm_node->ipv4) {
		sqbuf->ipv4 = true;

		iph = (struct iphdr *)buf;
		buf += sizeof(*iph);
		tcph = (struct tcphdr *)buf;
		buf += sizeof(*tcph);

		ether_addr_copy(ethh->h_dest, cm_node->rem_mac);
		ether_addr_copy(ethh->h_source, cm_node->loc_mac);
		if (cm_node->vlan_id <= VLAN_VID_MASK) {
			((struct vlan_ethhdr *)ethh)->h_vlan_proto = htons(ETH_P_8021Q);
			vtag = (cm_node->user_pri << VLAN_PRIO_SHIFT) | cm_node->vlan_id;
			((struct vlan_ethhdr *)ethh)->h_vlan_TCI = htons(vtag);

			((struct vlan_ethhdr *)ethh)->h_vlan_encapsulated_proto = htons(ETH_P_IP);
		} else {
			ethh->h_proto = htons(ETH_P_IP);
		}

		iph->version = IPVERSION;
		iph->ihl = 5;	/* 5 * 4Byte words, IP headr len */
		iph->tos = cm_node->tos;
		iph->tot_len = htons(packetsize);
		iph->id = htons(++cm_node->tcp_cntxt.loc_id);

		iph->frag_off = htons(0x4000);
		iph->ttl = 0x40;
		iph->protocol = IPPROTO_TCP;
		iph->saddr = htonl(cm_node->loc_addr[0]);
		iph->daddr = htonl(cm_node->rem_addr[0]);
	} else {
		sqbuf->ipv4 = false;
		ip6h = (struct ipv6hdr *)buf;
		buf += sizeof(*ip6h);
		tcph = (struct tcphdr *)buf;
		buf += sizeof(*tcph);

		ether_addr_copy(ethh->h_dest, cm_node->rem_mac);
		ether_addr_copy(ethh->h_source, cm_node->loc_mac);
		if (cm_node->vlan_id <= VLAN_VID_MASK) {
			((struct vlan_ethhdr *)ethh)->h_vlan_proto = htons(ETH_P_8021Q);
			vtag = (cm_node->user_pri << VLAN_PRIO_SHIFT) | cm_node->vlan_id;
			((struct vlan_ethhdr *)ethh)->h_vlan_TCI = htons(vtag);
			((struct vlan_ethhdr *)ethh)->h_vlan_encapsulated_proto = htons(ETH_P_IPV6);
		} else {
			ethh->h_proto = htons(ETH_P_IPV6);
		}
		ip6h->version = 6;
		ip6h->priority = cm_node->tos >> 4;
		ip6h->flow_lbl[0] = cm_node->tos << 4;
		ip6h->flow_lbl[1] = 0;
		ip6h->flow_lbl[2] = 0;
		ip6h->payload_len = htons(packetsize - sizeof(*ip6h));
		ip6h->nexthdr = 6;
		ip6h->hop_limit = 128;
		i40iw_copy_ip_htonl(ip6h->saddr.in6_u.u6_addr32,
				    cm_node->loc_addr);
		i40iw_copy_ip_htonl(ip6h->daddr.in6_u.u6_addr32,
				    cm_node->rem_addr);
	}

	tcph->source = htons(cm_node->loc_port);
	tcph->dest = htons(cm_node->rem_port);

	tcph->seq = htonl(cm_node->tcp_cntxt.loc_seq_num);

	if (flags & SET_ACK) {
		cm_node->tcp_cntxt.loc_ack_num = cm_node->tcp_cntxt.rcv_nxt;
		tcph->ack_seq = htonl(cm_node->tcp_cntxt.loc_ack_num);
		tcph->ack = 1;
	} else {
		tcph->ack_seq = 0;
	}

	if (flags & SET_SYN) {
		cm_node->tcp_cntxt.loc_seq_num++;
		tcph->syn = 1;
	} else {
		cm_node->tcp_cntxt.loc_seq_num += hdr_len + pd_len;
	}

	if (flags & SET_FIN) {
		cm_node->tcp_cntxt.loc_seq_num++;
		tcph->fin = 1;
	}

	if (flags & SET_RST)
		tcph->rst = 1;

	tcph->doff = (u16)((sizeof(*tcph) + opts_len + 3) >> 2);
	sqbuf->tcphlen = tcph->doff << 2;
	tcph->window = htons(cm_node->tcp_cntxt.rcv_wnd);
	tcph->urg_ptr = 0;

	if (opts_len) {
		memcpy(buf, options->addr, opts_len);
		buf += opts_len;
	}

	if (hdr_len) {
		memcpy(buf, hdr->addr, hdr_len);
		buf += hdr_len;
	}

	if (pdata && pdata->addr)
		memcpy(buf, pdata->addr, pdata->size);

	atomic_set(&sqbuf->refcount, 1);

	return sqbuf;
}