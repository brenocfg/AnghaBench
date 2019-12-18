#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_23__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_2__ roce; } ;
struct qedr_qp {int /*<<< orphan*/  sq_psn; } ;
struct qedr_dev {TYPE_3__* ndev; } ;
struct in6_addr {int dummy; } ;
struct TYPE_19__ {scalar_t__ csum; void* dport; void* sport; } ;
struct TYPE_18__ {void* daddr; void* saddr; int /*<<< orphan*/  ttl; void* frag_off; void* tos; int /*<<< orphan*/  protocol; } ;
struct TYPE_29__ {int /*<<< orphan*/  raw; } ;
struct TYPE_17__ {int /*<<< orphan*/  raw; } ;
struct TYPE_30__ {int flow_label; TYPE_8__ source_gid; TYPE_11__ destination_gid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; } ;
struct TYPE_28__ {void* source_qpn; void* qkey; } ;
struct TYPE_27__ {int solicited_event; int /*<<< orphan*/  opcode; void* psn; void* destination_qpn; int /*<<< orphan*/  pkey; } ;
struct TYPE_26__ {void* type; int /*<<< orphan*/  smac_h; int /*<<< orphan*/  dmac_h; } ;
struct TYPE_25__ {void* type; void* tag; } ;
struct ib_ud_header {TYPE_13__ udp; TYPE_12__ ip4; TYPE_9__ grh; TYPE_7__ deth; TYPE_6__ bth; TYPE_5__ eth; TYPE_4__ vlan; } ;
struct ib_send_wr {int num_sge; int send_flags; TYPE_1__* sg_list; } ;
struct ib_global_route {int flow_label; TYPE_11__ dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  traffic_class; struct ib_gid_attr* sgid_attr; } ;
struct TYPE_16__ {int /*<<< orphan*/  raw; } ;
struct ib_gid_attr {scalar_t__ gid_type; TYPE_10__ gid; } ;
struct TYPE_24__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_22__ {scalar_t__ length; } ;
struct TYPE_21__ {struct rdma_ah_attr attr; } ;
struct TYPE_20__ {int remote_qpn; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*) ; 
 scalar_t__ ETH_P_8021Q ; 
 scalar_t__ ETH_P_IBOE ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 scalar_t__ IP_DF ; 
 int QEDR_GSI_QPN ; 
 int /*<<< orphan*/  QEDR_ROCE_PKEY_DEFAULT ; 
 scalar_t__ QEDR_ROCE_V2_UDP_SPORT ; 
 int ROCE_V1 ; 
 int ROCE_V2_IPV4 ; 
 int ROCE_V2_IPV6 ; 
 scalar_t__ ROCE_V2_UDP_DPORT ; 
 scalar_t__ VLAN_CFI_MASK ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_15__* get_qedr_ah (int /*<<< orphan*/ ) ; 
 void* htonl (int) ; 
 void* htons (scalar_t__) ; 
 int ib_ud_header_init (int,int,int,int,int,int,int,int /*<<< orphan*/ ,struct ib_ud_header*) ; 
 scalar_t__ ipv6_addr_v4mapped (struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* qedr_get_ipv4_from_gid (int /*<<< orphan*/ ) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int rdma_read_gid_l2_fields (struct ib_gid_attr const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_14__* ud_wr (struct ib_send_wr const*) ; 

__attribute__((used)) static inline int qedr_gsi_build_header(struct qedr_dev *dev,
					struct qedr_qp *qp,
					const struct ib_send_wr *swr,
					struct ib_ud_header *udh,
					int *roce_mode)
{
	bool has_vlan = false, has_grh_ipv6 = true;
	struct rdma_ah_attr *ah_attr = &get_qedr_ah(ud_wr(swr)->ah)->attr;
	const struct ib_global_route *grh = rdma_ah_read_grh(ah_attr);
	const struct ib_gid_attr *sgid_attr = grh->sgid_attr;
	int send_size = 0;
	u16 vlan_id = 0;
	u16 ether_type;
	int rc;
	int ip_ver = 0;

	bool has_udp = false;
	int i;

	rc = rdma_read_gid_l2_fields(sgid_attr, &vlan_id, NULL);
	if (rc)
		return rc;

	if (vlan_id < VLAN_CFI_MASK)
		has_vlan = true;

	send_size = 0;
	for (i = 0; i < swr->num_sge; ++i)
		send_size += swr->sg_list[i].length;

	has_udp = (sgid_attr->gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP);
	if (!has_udp) {
		/* RoCE v1 */
		ether_type = ETH_P_IBOE;
		*roce_mode = ROCE_V1;
	} else if (ipv6_addr_v4mapped((struct in6_addr *)&sgid_attr->gid)) {
		/* RoCE v2 IPv4 */
		ip_ver = 4;
		ether_type = ETH_P_IP;
		has_grh_ipv6 = false;
		*roce_mode = ROCE_V2_IPV4;
	} else {
		/* RoCE v2 IPv6 */
		ip_ver = 6;
		ether_type = ETH_P_IPV6;
		*roce_mode = ROCE_V2_IPV6;
	}

	rc = ib_ud_header_init(send_size, false, true, has_vlan,
			       has_grh_ipv6, ip_ver, has_udp, 0, udh);
	if (rc) {
		DP_ERR(dev, "gsi post send: failed to init header\n");
		return rc;
	}

	/* ENET + VLAN headers */
	ether_addr_copy(udh->eth.dmac_h, ah_attr->roce.dmac);
	ether_addr_copy(udh->eth.smac_h, dev->ndev->dev_addr);
	if (has_vlan) {
		udh->eth.type = htons(ETH_P_8021Q);
		udh->vlan.tag = htons(vlan_id);
		udh->vlan.type = htons(ether_type);
	} else {
		udh->eth.type = htons(ether_type);
	}

	/* BTH */
	udh->bth.solicited_event = !!(swr->send_flags & IB_SEND_SOLICITED);
	udh->bth.pkey = QEDR_ROCE_PKEY_DEFAULT;
	udh->bth.destination_qpn = htonl(ud_wr(swr)->remote_qpn);
	udh->bth.psn = htonl((qp->sq_psn++) & ((1 << 24) - 1));
	udh->bth.opcode = IB_OPCODE_UD_SEND_ONLY;

	/* DETH */
	udh->deth.qkey = htonl(0x80010000);
	udh->deth.source_qpn = htonl(QEDR_GSI_QPN);

	if (has_grh_ipv6) {
		/* GRH / IPv6 header */
		udh->grh.traffic_class = grh->traffic_class;
		udh->grh.flow_label = grh->flow_label;
		udh->grh.hop_limit = grh->hop_limit;
		udh->grh.destination_gid = grh->dgid;
		memcpy(&udh->grh.source_gid.raw, sgid_attr->gid.raw,
		       sizeof(udh->grh.source_gid.raw));
	} else {
		/* IPv4 header */
		u32 ipv4_addr;

		udh->ip4.protocol = IPPROTO_UDP;
		udh->ip4.tos = htonl(grh->flow_label);
		udh->ip4.frag_off = htons(IP_DF);
		udh->ip4.ttl = grh->hop_limit;

		ipv4_addr = qedr_get_ipv4_from_gid(sgid_attr->gid.raw);
		udh->ip4.saddr = ipv4_addr;
		ipv4_addr = qedr_get_ipv4_from_gid(grh->dgid.raw);
		udh->ip4.daddr = ipv4_addr;
		/* note: checksum is calculated by the device */
	}

	/* UDP */
	if (has_udp) {
		udh->udp.sport = htons(QEDR_ROCE_V2_UDP_SPORT);
		udh->udp.dport = htons(ROCE_V2_UDP_DPORT);
		udh->udp.csum = 0;
		/* UDP length is untouched hence is zero */
	}
	return 0;
}