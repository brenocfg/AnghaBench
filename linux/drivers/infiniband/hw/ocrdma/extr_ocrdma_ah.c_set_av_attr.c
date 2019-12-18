#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union ib_gid {struct ocrdma_grh* raw; } ;
typedef  int u8 ;
typedef  int u16 ;
struct sockaddr_in6 {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct rdma_ah_attr {int dummy; } ;
struct ocrdma_grh {int* smac; int ttl; int protocol; int* sgid; int* dgid; void* pdid_hoplimit; void* tclass_flow; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; void* tot_len; void* frag_off; void* id; int /*<<< orphan*/ * dmac; void* eth_type; void* vlan_tag; void* roce_eth_type; } ;
struct ocrdma_eth_vlan {int* smac; int ttl; int protocol; int* sgid; int* dgid; void* pdid_hoplimit; void* tclass_flow; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; void* tot_len; void* frag_off; void* id; int /*<<< orphan*/ * dmac; void* eth_type; void* vlan_tag; void* roce_eth_type; } ;
struct ocrdma_eth_basic {int dummy; } ;
struct TYPE_4__ {struct ocrdma_grh* mac_addr; } ;
struct ocrdma_dev {int pvid; int sl; TYPE_1__ nic_info; int /*<<< orphan*/  id; scalar_t__ pfc_state; } ;
struct ocrdma_ah {scalar_t__ hdr_type; TYPE_3__* av; int /*<<< orphan*/  sgid_index; } ;
struct iphdr {int* smac; int ttl; int protocol; int* sgid; int* dgid; void* pdid_hoplimit; void* tclass_flow; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; void* tot_len; void* frag_off; void* id; int /*<<< orphan*/ * dmac; void* eth_type; void* vlan_tag; void* roce_eth_type; } ;
struct ib_global_route {int traffic_class; int hop_limit; int flow_label; union ib_gid const dgid; int /*<<< orphan*/  sgid_index; } ;
typedef  int /*<<< orphan*/  grh ;
typedef  int /*<<< orphan*/  eth ;
typedef  void* __be16 ;
struct TYPE_6__ {int eth_hdr; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_ALEN ; 
 int ETH_P_IBOE ; 
 int IP_DF ; 
 int /*<<< orphan*/  OCRDMA_AV_VLAN_VALID ; 
 int OCRDMA_VID_PCP_SHIFT ; 
 scalar_t__ RDMA_NETWORK_IPV4 ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (int*,struct ocrdma_grh*,int) ; 
 int /*<<< orphan*/  memset (struct ocrdma_grh*,int /*<<< orphan*/ ,int) ; 
 int ocrdma_hdr_type_to_proto_num (int /*<<< orphan*/ ,scalar_t__) ; 
 int ocrdma_resolve_dmac (struct ocrdma_dev*,struct rdma_ah_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 struct ib_global_route* rdma_ah_read_grh (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_gid2ip (struct sockaddr*,union ib_gid const*) ; 

__attribute__((used)) static inline int set_av_attr(struct ocrdma_dev *dev, struct ocrdma_ah *ah,
			struct rdma_ah_attr *attr, const union ib_gid *sgid,
			int pdid, bool *isvlan, u16 vlan_tag)
{
	int status;
	struct ocrdma_eth_vlan eth;
	struct ocrdma_grh grh;
	int eth_sz;
	u16 proto_num = 0;
	u8 nxthdr = 0x11;
	struct iphdr ipv4;
	const struct ib_global_route *ib_grh;
	union {
		struct sockaddr_in  _sockaddr_in;
		struct sockaddr_in6 _sockaddr_in6;
	} sgid_addr, dgid_addr;

	memset(&eth, 0, sizeof(eth));
	memset(&grh, 0, sizeof(grh));

	/* Protocol Number */
	proto_num = ocrdma_hdr_type_to_proto_num(dev->id, ah->hdr_type);
	if (!proto_num)
		return -EINVAL;
	nxthdr = (proto_num == ETH_P_IBOE) ? 0x1b : 0x11;
	/* VLAN */
	if (!vlan_tag || (vlan_tag > 0xFFF))
		vlan_tag = dev->pvid;
	if (vlan_tag || dev->pfc_state) {
		if (!vlan_tag) {
			pr_err("ocrdma%d:Using VLAN with PFC is recommended\n",
				dev->id);
			pr_err("ocrdma%d:Using VLAN 0 for this connection\n",
				dev->id);
		}
		eth.eth_type = cpu_to_be16(0x8100);
		eth.roce_eth_type = cpu_to_be16(proto_num);
		vlan_tag |= (dev->sl & 0x07) << OCRDMA_VID_PCP_SHIFT;
		eth.vlan_tag = cpu_to_be16(vlan_tag);
		eth_sz = sizeof(struct ocrdma_eth_vlan);
		*isvlan = true;
	} else {
		eth.eth_type = cpu_to_be16(proto_num);
		eth_sz = sizeof(struct ocrdma_eth_basic);
	}
	/* MAC */
	memcpy(&eth.smac[0], &dev->nic_info.mac_addr[0], ETH_ALEN);
	status = ocrdma_resolve_dmac(dev, attr, &eth.dmac[0]);
	if (status)
		return status;
	ib_grh = rdma_ah_read_grh(attr);
	ah->sgid_index = ib_grh->sgid_index;
	/* Eth HDR */
	memcpy(&ah->av->eth_hdr, &eth, eth_sz);
	if (ah->hdr_type == RDMA_NETWORK_IPV4) {
		*((__be16 *)&ipv4) = htons((4 << 12) | (5 << 8) |
					   ib_grh->traffic_class);
		ipv4.id = cpu_to_be16(pdid);
		ipv4.frag_off = htons(IP_DF);
		ipv4.tot_len = htons(0);
		ipv4.ttl = ib_grh->hop_limit;
		ipv4.protocol = nxthdr;
		rdma_gid2ip((struct sockaddr *)&sgid_addr, sgid);
		ipv4.saddr = sgid_addr._sockaddr_in.sin_addr.s_addr;
		rdma_gid2ip((struct sockaddr*)&dgid_addr, &ib_grh->dgid);
		ipv4.daddr = dgid_addr._sockaddr_in.sin_addr.s_addr;
		memcpy((u8 *)ah->av + eth_sz, &ipv4, sizeof(struct iphdr));
	} else {
		memcpy(&grh.sgid[0], sgid->raw, sizeof(union ib_gid));
		grh.tclass_flow = cpu_to_be32((6 << 28) |
					      (ib_grh->traffic_class << 24) |
					      ib_grh->flow_label);
		memcpy(&grh.dgid[0], ib_grh->dgid.raw,
		       sizeof(ib_grh->dgid.raw));
		grh.pdid_hoplimit = cpu_to_be32((pdid << 16) |
						(nxthdr << 8) |
						ib_grh->hop_limit);
		memcpy((u8 *)ah->av + eth_sz, &grh, sizeof(struct ocrdma_grh));
	}
	if (*isvlan)
		ah->av->valid |= OCRDMA_AV_VLAN_VALID;
	ah->av->valid = cpu_to_le32(ah->av->valid);
	return status;
}